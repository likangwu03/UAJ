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
		// las b�squedas modernas se utilizan para recorrer un contenedor de elementos completo
		for (auto client : group) {
			client->getComponent<ClientMovement>()->recolocateEntrance();
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

	// n�mero de clientes que hay en el grupo
	int num = sdl->rand().nextInt(1, 5);
	for (int i = num - 1; i >= 0; --i) {
		group.push_back(createClient(i));
	}

	entrance.push_back(group);
	clientsGroups.push_back(group);

	for (auto client : group) {
		client->getComponent<ClientMovement>()->setGroup(group);
	}
}

Client* ClientsManager::createClient(int posGroup) {
	string sprite = "Client_" + to_string(sdl->rand().nextInt(1, 10));

	// a partir de la posici�n el grupo se calcula donde empieza
	Vector origin = _ecs::OUT_ENTRY;
	origin.setY(origin.getY() - posGroup);

	return new Client(scene, sprite, RelativeToGlobal::point(origin), menu, entrance.size(), speed, posGroup);
}

void ClientsManager::checkCashRegister() {
	// lista de grupos
	for (auto group : clientsGroups) {
		// se recorre cada cliente del grupo
		for (auto client : group) {
			if (client->getComponent<ClientState>()->getState() == ClientState::CASH_REGISTER) {
				// Client* client = dynamic_cast<Client*> (object);
				// se le indica la posici�n a ocupar en la cola
				client->getComponent<ClientMovement>()->setPosPay(pay.size());
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

bool ClientsManager::notAbandonedEntrance(Client* client) {
	return !client->getComponent<ClientMovement>()->hasAbandonedEntrance();
}

void ClientsManager::checkHappinessEntrance() {
	// encontrar a un grupo en el que todos sus integrantes han abandonado la entrada
	bool found = false;
	auto it = entrance.begin();
	while (it != entrance.end() && !found) {
		vector<Client*> group = *it;
		// hasta que todos los clientes del grupo no hayan abandonado la entrada,
		// no se elimina el grupo de la entrada
		// se busca uno que no haya abandonado la entrada y si no se encuentra,
		// es que todos la han abandonado
		found = std::find_if(group.begin(), group.end(), notAbandonedEntrance) == group.end();

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
	for (auto it = pay.begin(); it != pay.end(); it) {
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

bool ClientsManager::deskIsNotOccupied(DeskComp* desk) {
	return !desk->isOccupied();
}

bool ClientsManager::checkFirstTableEmpty(int& table) {
	auto it = std::find_if(tables.begin(), tables.end(), deskIsNotOccupied);
	// se ha encontrado una mesa no ocupada
	if (it != tables.end()) {
		table = (*it)->getID();
		return true;
	}
	return false;
}

void ClientsManager::assignTable(int table, vector<Client*> firstGroup) {
	// se le asigna la mesa a cada miembro del grupo
	for (auto client : firstGroup) {
		client->getComponent<ClientMovement>()->assignTable(table);
	}

	// se asigna el grupo de clientes a la mesa
	tables[table - 1]->assignClients(firstGroup);

	assignedClient = true;
}

/*
void ClientsManager::checkTables() {
	for (auto it = clientsGroups.begin(); it != clientsGroups.end(); ++it) {
		// se utiliza el primer integrante del grupo para comprobar que se ha dejado la mesa
		// se hace de esta manera por el orden de ejecuci�n
		// (uno se marcha e indica al resto del grupo que se marchen.
		// En la siguiente iteraci�n tres est�n abandonado la mesa y el otro ya se ha marchado
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
*/

// comprobar si un cliente si un cliente est� de camino a pagar o pagando
bool ClientsManager::isPaying(GameObject* client) {
	ClientState* state = client->getComponent<ClientState>();
	ClientState::States currentState = state->getState();

	return currentState == ClientState::HAS_LEFT ||
		currentState == ClientState::REGISTER ||
		currentState == ClientState::CASH_REGISTER ||
		currentState == ClientState::PAYING;
}

bool ClientsManager::notOutOfLocal(Client* client) {
	return client->getComponent<ClientState>()->getState() != ClientState::OUT;
}

// comprobar si alg�n grupo ha abandonado el local para quitarlo de la lista
void ClientsManager::refreshClientsGroup() {
	bool found = true;
	auto it = clientsGroups.begin();
	while (it != clientsGroups.end() && found) {
		vector<Client*> group = *it;

		// se comprueba que todos los integrantes del grupo est�n saliendo del local
		found = std::find_if(group.begin(), group.end(), notOutOfLocal) != group.end();

		if (!found) {
			it = clientsGroups.erase(it);
		}
		if (it != clientsGroups.end()) {
			++it;
		}
	}
}

ClientsManager::ClientsManager(GameObject* parent, vector<_ecs::_dish_id> menu, float frequencyClients, float speedClients, int maxClients)
	: Manager(parent), menu(menu), timer(frequencyClients), speed(speedClients), assignedClient(false), maxClients(maxClients), tables() {
	scene = parent->getScene();
	sdl = SDLUtils::instance();
	lastClientTime = sdl->currRealTime();
}

void ClientsManager::assignFirstGroup(int table) {
	if (!isEntranceEmpty()) {
		// se coge el primer cliente
		vector<Client*> firstGroup = getFirstEntrance();
		// con que se compruebe que el primero del grupo est� en la entrada,
		// vale para verificar que todo el grupo est� en la entrada
		Client* firstClient = firstGroup.front();
		ClientState::States clientState = firstClient->getComponent<ClientState>()->getState();
		if (clientState == ClientState::ENTRANCE) {
			if (!tables[table - 1]->isOccupied()) {
				assignTable(table, firstGroup);
			}
			else {
				int table = -1;
				if (checkFirstTableEmpty(table) && table < 3) {
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
	for (auto group : clientsGroups) {
		// con que uno del grupo est� en una de esas posiciones,
		// todos los del grupo est�n en la misma

		// no se cuenta el grupo que quiere ocupar la caja
		Client* client = group.front();
		if (client != mates.front()) {
			// se cuenta el resto de grupos
			if (isPaying(client)) {
				// se le suma el n�mero de integrantes del grupo
				goingPay = goingPay + group.size();
			}
		}
	}
	// n�mero de clientes que quiere ir + n�mero de clientes que hay de camino a la caja o pagando
	if (mates.size() + goingPay <= MAX_PAY) {
		return true;
	}
	else {
		return false;
	}
}

void ClientsManager::initTables() {
	for (auto obj : *scene->getGroup(_ecs::grp_DESK)) {
		DeskComp* desk = obj->getComponent<DeskComp>();
		tables[desk->getID() - 1] = desk;
	}
}

void ClientsManager::update() {
	// se a�ade con frecuencia un cliente
	addFrequently();

	// se comprueba si se ha asignado el primer grupo a una mesa para quitarlo de la entrada
	firstClientAssigned();

	// a�adir los clientes que han llegado a la caja registradora a la cola de pago
	checkCashRegister();

	// eliminar grupos de clientes enfadados de la entrada
	checkHappinessEntrance();

	// marcar como desocupadas las mesas de las que los clientes se han marchado
	// (han terminado de comer o se han quedado sin felicidad)
	// checkTables();

	// eliminar grupos de clientes enfadados de la cola de pagar
	checkHappinessPay();

	refreshClientsGroup();
}