#include "./ClientsManager.h"
#include "../components/DeskComp.h"

void ClientsManager::addFrequently() {
	if (clientsGroups.size() < maxClients && entrance.size() < MAX_ENTRANCE) {
		float time = sdl->currRealTime() - lastClientTime;
		if (time > timer) {
			lastClientTime = sdl->currRealTime();
			// se crea un nuevo grupo de clientes
			createGroupClients();
		}
	}
	else {
		lastClientTime = sdl->currRealTime();
	}
}

void ClientsManager::recolocateEntranceAll(std::list<vector<Client*>>::iterator it) {
	for (it; it != entrance.end(); ++it) {
		vector<Client*> group = *it;
		for (int i = 0; i < group.size(); ++i) {
			group[i]->getComponent<ClientMovement>()->recolocateEntrance();
		}
	}
}

void ClientsManager::recolocatePayAll(std::list<Client*>::iterator it) {
	for (it; it != pay.end(); ++it) {
		Client* c = *it;
		c->getComponent<ClientMovement>()->recolotatePay();
	}
}

void ClientsManager::createGroupClients() {
	vector<Client*> group;

	// número de clientes que hay en el grupo
	int num = sdl->rand().nextInt(1, 5);
	for (int i = num - 1; i >= 0; --i) {
		group.push_back(createClient(i));
	}

	entrance.push_back(group);
	clientsGroups.push_back(group);

	for (int i = 0; i < group.size(); ++i) {
		group[i]->getComponent<ClientMovement>()->setGroup(group);
	}
}

Client* ClientsManager::createClient(int posGroup) {
	string sprite = "Client_" + to_string(sdl->rand().nextInt(1, 10));

	// a partir de la posición el grupo se calcula donde empieza
	Vector origin = _ecs::OUT_ENTRY;
	origin.setY(origin.getY() - posGroup);

	return new Client(scene, sprite, RelativeToGlobal::point(origin), menu, entrance.size(), speed, posGroup);
}

void ClientsManager::checkCashRegister() {
	// lista de grupos
	for (auto it = clientsGroups.begin(); it != clientsGroups.end(); ++it) {
		vector<Client*> group = *it;
		// grupo
		for (int i = 0; i < group.size(); ++i) {
			Client* g = group[i];
			if (g->getComponent<ClientState>()->getState() == ClientState::CASH_REGISTER) {
				Client* client = dynamic_cast<Client*> (g);
				// se le indica la posición a ocupar en la cola
				g->getComponent<ClientMovement>()->setPosPay(pay.size());
				pay.push_back(client);
			}
		}
	}
}

void ClientsManager::firstClientAssigned() {
	if (assignedClient) {
		entrance.pop_front();
		recolocateEntranceAll(entrance.begin());
		assignedClient = false;
	}
}

void ClientsManager::checkHappinessEntrance() {
	bool found = false;	// encontrar a un grupo en el que uno de sus integrantes ha abandonado la entrada
	auto it = entrance.begin();
	while (it != entrance.end() && !found) {
		vector<Client*> group = *it;
		int i = 0;
		found = true;
		// hasta que todos los clientes del grupo no hayan abandonado la entrada,
		// no se elimina el grupo de la entrada
		while (i < group.size() && found) {
			if (!group[i]->getComponent<ClientMovement>()->hasAbandonedEntrance()) {
				found = false;
			}
			++i;
		}
		// si todos han abandonado la entrada se elimina el grupo
		if (found) {
			it = entrance.erase(it);
			recolocateEntranceAll(it);
		}
		if (it != entrance.end()) {
			++it;
		}
	}
}

void ClientsManager::checkHappinessPay() {
	// se utiliza un for porque los clientes de un mismo grupo, la abandonan a la vez
	auto it = pay.begin();
	for (it; it != pay.end(); it) {
		Client* client = (*it);
		bool found = false;
		// si uno de los clientes ha abandonado la caja, se elimian y se recoloca
		if (client->getComponent<ClientMovement>()->hasAbandonedPay()) {
			it = pay.erase(it);
			recolocatePayAll(it);
			found = true;
		}
		// si no se ha eliminado ninguno se avanza el iterador
		// en caso contrario, no se toca porque ya ha avanzado
		if (!found && it != pay.end()) {
			++it;
		}
	}
}

bool ClientsManager::checkFirstTableEmpty(int& table) {
	bool found = false;
	int i = 0;
	while (i < _ecs::NUM_TABLES && !found) {
		if (!tables[i]->isOccupied()) {
			found = true;
			table = i + 1;
		}
		++i;
	}
	return found;
}

void ClientsManager::assignTable(int table, vector<Client*> firstGroup) {
	// se le asigna una mesa a cada miembro del grupo
	for (int i = 0; i < firstGroup.size(); ++i) {
		firstGroup[i]->getComponent<ClientMovement>()->assignTable(table);
	}
	// Se asigna el grupo de clientes a la mesa
	tables[table - 1]->assignClients(firstGroup);

	assignedClient = true;
}

void ClientsManager::checkTables() {
	for (auto it = clientsGroups.begin(); it != clientsGroups.end(); ++it) {
		// se utiliza el primer integrante del grupo para comprobar que se ha dejado la mesa
		// se hace de esta manera por el orden de ejecución
		// (uno se marcha e indica al resto del grupo que se marchen.
		// En la siguiente iteración tres están abandonado la mesa y el otro ya se ha marchado
		// Entonces, si se comprueba todo el grupo sale mal)
		Client* c = (*it).front();
		ClientMovement* m = c->getComponent<ClientMovement>();
		ClientState* s = c->getComponent<ClientState>();
		if (s->getState() == ClientState::HAS_LEFT
			|| m->hasAbandonedTable()) {
			// se marca la mesa como desocupada
			int n = m->getAssignedTable() - 1;
			//tables[n] = false;
		}
	}
}

// comprobar si un cliente si un cliente está de camino a pagar o pagando
bool ClientsManager::isPaying(GameObject* client) {
	ClientState* state = client->getComponent<ClientState>();
	ClientState::States currentState = state->getState();
	if (currentState == ClientState::HAS_LEFT ||
		currentState == ClientState::REGISTER ||
		currentState == ClientState::CASH_REGISTER ||
		currentState == ClientState::PAYING) {
		return true;
	}
	return false;
}

// comprobar si algún grupo ha abandonado el local para quitarlo de la lista
void ClientsManager::refreshClientsGroup() {
	bool found = true;
	auto it = clientsGroups.begin();
	while (it != clientsGroups.end() && found) {
		vector<Client*> group = *it;
		found = false;
		int i = 0;
		// se comprueba que todos los integrantes del grupo están saliendo del local
		while (i < group.size() && !found) {
			if (group[i]->getComponent<ClientState>()->getState() != ClientState::OUT) {
				found = true;
			}
			++i;
		}
		// si no se ha encontrado ningún cliente del grupo que no esté saliendo del local,
		// se quita de la lista
		if (!found) {
			it = clientsGroups.erase(it);
		}
		if (it != clientsGroups.end()) {
			++it;
		}
	}
}

ClientsManager::ClientsManager(GameObject* parent, vector<_ecs::_dish_id> menu, float frequencyClients, float speedClients, int maxClients)
	: Manager(parent), menu(menu), timer(frequencyClients), speed(speedClients), assignedClient(false), maxClients(maxClients) {
	scene = parent->getScene();
	sdl = SDLUtils::instance();
	lastClientTime = sdl->currRealTime();
}

void ClientsManager::assignFirstGroup(int table) {
	if (!isEntranceEmpty()) {
		// se coge el primer cliente
		vector<Client*> firstGroup = getFirstEntrance();
		// con que se compruebe que el primero del grupo está en la entrada,
		// vale para verificar que todo el grupo está en la entrada
		Client* firstClient = firstGroup.front();
		ClientState::States clientState = firstClient->getComponent<ClientState>()->getState();
		if (clientState == ClientState::ENTRANCE) {
			if (!tables[table - 1]->isOccupied()) {
				assignTable(table, firstGroup);
			}
			else {
				int table = -1;
				if (checkFirstTableEmpty(table)) {
					assignTable(table, firstGroup);
				}
			}
		}
	}
}

void ClientsManager::collectAndLeave() {
	while (pay.size() > 0) {
		Client* firstPay = pay.front();
		firstPay->getComponent<ClientMovement>()->payAndLeave();
		pay.pop_front();
		auto it = pay.begin();
		recolocatePayAll(it);
	}
}

bool ClientsManager::canOccupyPay(vector<Client*> mates) {
	int goingPay = 0;
	for (auto it = clientsGroups.begin(); it != clientsGroups.end(); ++it) {
		// con que uno del grupo esté en una de esas posiciones,
		// todos los del grupo están en la misma

		// no se cuenta el grupo que quiere ocupar la caja
		Client* client = (*it).front();
		if (client != mates.front()) {
			// se cuenta el resto de grupos
			if (isPaying(client)) {
				// se le suma el número de integrantes del grupo
				goingPay = goingPay + it->size();
			}
		}
	}
	// número de clientes que quiere ir + número de clientes que hay de camino a la caja o pagando
	if (mates.size() + goingPay <= MAX_PAY) {
		return true;
	}
	else {
		return false;
	}
}

void ClientsManager::update() {
	// se añade con frecuencia un cliente
	addFrequently();

	// se comprueba si se ha asignado el primer grupo a una mesa para quitarlo de la entrada
	firstClientAssigned();

	// añadir los clientes que han llegado a la caja registradora a la cola de pago
	checkCashRegister();

	// eliminar grupos de clientes enfadados de la entrada
	checkHappinessEntrance();

	// marcar como desocupadas las mesas de las que los clientes se han marchado
	// (han terminado de comer o se han quedado sin felicidad)
	//checkTables();

	// eliminar grupos de clientes enfadados de la cola de pagar
	checkHappinessPay();

	refreshClientsGroup();
}

void ClientsManager::getTables() {
	for (auto obj : *scene->getGroup(_ecs::grp_DESK)) {
		DeskComp* desk = obj->getComponent<DeskComp>();
		// duck typing para comprobar si el objeto interactuable es una mesa
		if (desk != nullptr) {
			tables[desk->getID() - 1] = desk;
		}
	}
}