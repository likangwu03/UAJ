#pragma once

#include "../gameObjects/Client.h"
#include "../structure/Manager.h"
#include "../structure/Scene.h"
#include "../structure/Paths_def.h"
#include <vector>
#include <list>
#include <iostream>

using namespace std;

class ClientsManager : public Manager<ClientsManager> {

	// dar acceso al constructor privado a la clase Manager, de la que hereda
	friend Manager<ClientsManager>;

private:
	// cola con la entrada
	list<Client*> entrance;
	// cola con la caja de pagar
	list<Client*> pay;
	// puntero al grupo con todos los clientes
	vector<GameObject*>* clients;
	vector<_ecs::_dish_id> menu;
	Scene* scene;
	SDLUtils* sdl;
	float lastClientTime;
	float timer;
	float speed;
	bool assignedCustomer;

	const int MAX_CLIENTS = 6;
	const int MAX_ENTRANCE = 3;

	// testeo
	const int TEST_ENTRANCE = 3;
	const int TEST_PAY = 4;

	void addFrequently() {
		if (clients->size() < MAX_CLIENTS && entrance.size() < MAX_ENTRANCE) {
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

	bool isEntranceEmpty() {
		return entrance.size() == 0;
	}

	void recolocateEntranceAll(std::list<Client*>::iterator it) {
		for (it; it != entrance.end(); ++it) {
			Client* c = *it;
			c->getComponent<ClientMovement>()->recolocateEntrance();
		}
	}

	void recolocatePayAll(std::list<Client*>::iterator it) {
		for (it; it != pay.end(); ++it) {
			Client* c = *it;
			c->getComponent<ClientMovement>()->recolotatePay();
		}
	}

	void createClient() {
		string sprite = "Customer_" + to_string(sdl->rand().nextInt(1, 9));
		entrance.push_back(new Client(scene, sprite, _ecs::OUT, menu, entrance.size(), speed));
	}

	// se comprueba si algún cliente ha llegado a la caja registrado y se añade a la cola de pagar
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

	void firstClientAssigned() {
		if (assignedCustomer) {
			entrance.pop_front();
			recolocateEntranceAll(entrance.begin());
			assignedCustomer = false;
		}
	}

	ClientsManager(GameObject* parent, vector<_ecs::_dish_id> menu, float frequencyClients) 
		: Manager(parent), menu(menu), timer(frequencyClients), speed(2), lastClientTime(0), assignedCustomer(false) {
		scene = parent->getScene();
		clients = scene->getGroup(_ecs::grp_CLIENTS);
		sdl = SDLUtils::instance();
	}

	int test() const {
		int table = sdl->rand().nextInt(1, 5);
		if (table == 3) {
			table = 4;
		}
		return table;
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
	// para que se vaya actualizando dinámicamente
	list<Client*>* getPayQueue() {
		return &pay;
	}

	// se llama cuando se quiera asignar una mesa al primer cliente
	// se le pasa la mesa que se le desea asignar
	// devuelve un booleano para confirmar si se ha podido asignar o no
	// porque solo se puede hacer cuando la cola no está vacía y el primer cliente está en la entrada
	bool assignFirstClient(int table) {
		if (!isEntranceEmpty()) {
			// se coge el primer cliente
			Client* firstEntrance = getFirstEntrance();
			// se comprueba que el cliente está en la entrada
			ClientState::States clientState = firstEntrance->getComponent<ClientState>()->getState();
			if (clientState == ClientState::ENTRANCE) {
				// se le asigna una mesa
				firstEntrance->getComponent<ClientMovement>()->assignTable(table);
				assignedCustomer = true;
				return true;
			}
		}
		return false;
	}

	// se llama cuando se quiere cobrar a los clientes que hay en la caja registradora
	// el método solo de moverlos
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

		// testo
		if (entrance.size() == TEST_ENTRANCE) {
			assignFirstClient(test());
		}
		
		firstClientAssigned();

		checkCashRegister();

		// testeo
		if (pay.size() >= TEST_PAY) {
			collectAndLeave();
		}
	}
};