#pragma once

#include "../gameObjects/Client.h"
#include "../structure/Manager.h"
#include "../structure/Scene.h"
#include "../structure/Paths_def.h"
#include <vector>
#include <list>
#include <array>

using namespace std;

class ClientsManager : public Manager<ClientsManager> {

	// dar acceso al constructor privado a la clase Manager, de la que hereda
	friend Manager<ClientsManager>;

private:
	// TESTEO
	const int TEST_ENTRANCE = 3;
	const int TEST_PAY = 4;

	const int MAX_ENTRANCE = 3;
	const int MAX_PAY = 8;

	// cola con la entrada
	list<Client*> entrance;
	// cola con la caja de pagar
	list<Client*> pay;
	// puntero al grupo con todos los clientes
	vector<GameObject*>* clients;
	// menú del día
	vector<_ecs::_dish_id> menu;
	Scene* scene;
	SDLUtils* sdl;
	float lastClientTime;
	float timer;
	float speed;
	int maxClients;
	// indica si el primer cliente en la entra se ha asignado o no
	bool assignedClient;
	// indicar si las mesas están ocupadas o no
	bool tables[_ecs::NUM_TABLES];

	// añadir un cliente cada cierto tiempo
	void addFrequently() {
		if (clients->size() < maxClients && entrance.size() < MAX_ENTRANCE) {
			float time = sdl->currRealTime() - lastClientTime;
			if (time > timer) {
				lastClientTime = sdl->currRealTime();
				// se crea un nuevo cliente
				createClient();
			}
		}
		else {
			lastClientTime = sdl->currRealTime();
		}
	}

	// comprobar si la entrada está vacía
	bool isEntranceEmpty() {
		return entrance.size() == 0;
	}

	// recolar en la entrada al resto si se ha ido algún cliente
	void recolocateEntranceAll(std::list<Client*>::iterator it) {
		for (it; it != entrance.end(); ++it) {
			Client* c = *it;
			c->getComponent<ClientMovement>()->recolocateEntrance();
		}
	}

	// recolocar en la caja al resto si se ha ido algún cliente
	void recolocatePayAll(std::list<Client*>::iterator it) {
		for (it; it != pay.end(); ++it) {
			Client* c = *it;
			c->getComponent<ClientMovement>()->recolotatePay();
		}
	}

	// crear un cliente
	void createClient() {
		string sprite = "Client_" + to_string(sdl->rand().nextInt(1, 10));
		entrance.push_back(new Client(scene, sprite, relativeToGlobal(_ecs::OUT_ENTRY), menu, entrance.size(), speed));
	}

	// comprobar si algún cliente ha llegado a la caja registradora y añadirlo a la cola de pagar
	void checkCashRegister() {
		for (int i = 0; i < clients->size(); ++i) {
			GameObject* g = (*clients)[i];
			if (g->getComponent<ClientState>()->getState() == ClientState::CASH_REGISTER) {
				Client* client = dynamic_cast<Client*> (g);
				// se le indica la posición a ocupar en la cola
				g->getComponent<ClientMovement>()->setPosPay(pay.size());
				pay.push_back(client);
			}
		}
	}

	// eliminar al primer cliente de la entrada si se le ha asignado una mesa
	void firstClientAssigned() {
		if (assignedClient) {
			entrance.pop_front();
			recolocateEntranceAll(entrance.begin());
			assignedClient = false;
		}
	}

	// convertir un punto relativo en global
	Vector relativeToGlobal(const Vector& point) {
		int fWidth = sdl->width() / 40;
		int fHeight = sdl->height() / 23;
		return Vector(point.getX() * fWidth, point.getY() * fHeight);
	}

	// comprobar si un cliente de la entrada se tiene que marchar porque se queda sin felicidad
	void checkHappinessEntrance() {
		bool found = false;
		auto it = entrance.begin();
		while (it != entrance.end() && !found) {
			Client* client = (*it);
			if (client->getComponent<ClientMovement>()->hasAbandonedEntrance()) {
				it = entrance.erase(it);
				recolocateEntranceAll(it);
				found = true;
			}
			if (it != entrance.end()) {
				++it;
			}
		}
	}

	// igual que el método anterior, pero para la caja
	void checkHappinessPay() {
		bool found = false;
		auto it = pay.begin();
		while (it != pay.end() && !found) {
			Client* client = (*it);
			if (client->getComponent<ClientMovement>()->hasAbandonedPay()) {
				it = pay.erase(it);
				recolocatePayAll(it);
				found = true;
			}
			if (it != pay.end()) {
				++it;
			}
		}
	}

	// comprobar si una mesa está ocupada o no
	bool isTableFull(int table) const {
		return tables[table - 1];
	}

	// encontrar la primera mesa vacía
	bool checkFirstTableEmpty(int& table) {
		bool found = false;
		int i = 0;
		while( i < _ecs::NUM_TABLES && !found) {
			if (!tables[i]) {
				found = true;
				table = i + 1;
			}
			++i;
		}
		return found;
	}

	// asignar una mesa al primer cliente
	void assignTable(int table, Client* firstEntrance) {
		// se marca que la mesa está ocupada
		tables[table - 1] = true;
		// se le asigna una mesa
		firstEntrance->getComponent<ClientMovement>()->assignTable(table);
		assignedClient = true;
	}

	// comprobar si algún cliente ha abandonado una mesa o si ha terminado de comer para marcarla como desocupada
	void checkTables() {
		for (int i = 0; i < clients->size(); ++i) {
			GameObject* g = (*clients)[i];
			ClientMovement* m = g->getComponent<ClientMovement>();
			if (g->getComponent<ClientState>()->getState() == ClientState::FINISH_EAT ||
				(m->hasAbandonedTable())) {
				tables[m->getAssignedTable() - 1] = false;
			}
		}
	}

	ClientsManager(GameObject* parent, vector<_ecs::_dish_id> menu, float frequencyClients, float speedClients, int maxClients)
		: Manager(parent), menu(menu), timer(frequencyClients), speed(speedClients), assignedClient(false), maxClients(maxClients) {
		scene = parent->getScene();
		clients = scene->getGroup(_ecs::grp_CLIENTS);
		sdl = SDLUtils::instance();
		lastClientTime = sdl->currRealTime();
		for (int i = 0; i < _ecs::NUM_TABLES; ++i) {
			tables[i] = false;
		}
	}

public:

	static constexpr _ecs::_cmp_id id = _ecs::cmp_CLIENTS_MANAGER;

	// devuelve el primer cliente que hay en la entrada esperando a ser atendido
	// nullptr en caso de que la entrada esté vacía
	Client* getFirstEntrance() {
		if (isEntranceEmpty()) {
			return nullptr;
		}
		return entrance.front();
	}

	// devuelve un puntero a la cola de la caja
	list<Client*>* getPayQueue() {
		return &pay;
	}

	// se llama cuando se quiera asignar una mesa al primer cliente
	// se le pasa la mesa que se le desea asignar
	void assignFirstClient(int table) {
		if (!isEntranceEmpty()) {
			// se coge el primer cliente
			Client* firstEntrance = getFirstEntrance();
			// se comprueba que el cliente está en la entrada
			ClientState::States clientState = firstEntrance->getComponent<ClientState>()->getState();
			if (clientState == ClientState::ENTRANCE) {
				if (!isTableFull(table)) {
					assignTable(table, firstEntrance);
				}
				else {
					int table = -1;
					if (checkFirstTableEmpty(table)) {
						assignTable(table, firstEntrance);
					}
				}
			}
		}
	}

	// se llama cuando se quiere cobrar a los clientes que hay en la caja registradora
	void collectAndLeave() {
		while (pay.size() > 0) {
			Client* firstPay = pay.front();
			firstPay->getComponent<ClientMovement>()->payAndLeave();
			pay.pop_front();
			auto it = pay.begin();
			recolocatePayAll(it);
		}
	}

	void update() {
		// se añade con frecuencia un cliente
		addFrequently();

		/*
		// TESTEO
		if (entrance.size() == TEST_ENTRANCE) {
			assignFirstClient(test());
		}
		*/

		// se comprueba si se ha asignado el primer cliente a una mesa para quitarlo de la entrada
		firstClientAssigned();

		// añadir los clientes que han llegado a la caja registradora a la cola de pago
		checkCashRegister();

		/*
		// TESTEO
		if (pay.size() >= TEST_PAY) {
			collectAndLeave();
		}
		*/

		// eliminar clientes enfadados de la entrada
		checkHappinessEntrance();

		// marcar como desucpadas a las mesas en las que clientes se han marchado
		// (han terminado de comer o se han quedado sin felicidad)
		checkTables();

		// eliminar clientes enfadados de la cola de pagar
		checkHappinessPay();
	}
};