#pragma once

#include "../gameObjects/Client.h"
#include "../structure/Manager.h"
#include "../structure/Scene.h"
#include "../structure/Paths_def.h"
#include "../utils/checkML.h"
#include "../objects/RelativeToGlobal.h"
#include <vector>
#include <list>

using namespace std;

class ClientsManager : public Manager<ClientsManager> {

	// dar acceso al constructor privado a la clase Manager, de la que hereda
	friend Manager<ClientsManager>;

private:

	const int MAX_ENTRANCE = 3;
	const int MAX_PAY = 7;

	// cola con la entrada
	list<vector<Client*>> entrance;
	// cola con la caja de pagar
	// los clientes se colocan todos en fila
	list<Client*> pay;
	// lista con los grupos de clientes
	list<vector<Client*>> clientsGroups;
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
	void addFrequently();

	// comprobar si la entrada está vacía
	inline bool isEntranceEmpty() {
		return entrance.size() == 0;
	}

	// recolar en la entrada al resto si se ha ido algún cliente
	void recolocateEntranceAll(std::list<vector<Client*>>::iterator it);

	// recolocar en la caja al resto si se ha ido algún cliente
	void recolocatePayAll(std::list<Client*>::iterator it);

	// crear un grupo de clientes
	void createGroupClients();

	// crear un cliente
	Client* createClient(int posGroup);

	// comprobar si algún cliente ha llegado a la caja registradora y añadirlo a la cola de pagar
	// se añaden todos los clientes, sin importar del grupo que sean, en fila
	void checkCashRegister();

	// eliminar al primer grupo de clientes si se le ha asignado una mesa
	void firstClientAssigned();

	// comprobar si un grupo de clientes de la entrada se tiene que marchar porque se queda sin felicidad
	void checkHappinessEntrance();

	// comprobar si algún grupo de cliente de la caja se ha quedado sin felicidad y se ha marchado
	void checkHappinessPay();

	// comprobar si una mesa está ocupada o no
	inline bool isTableFull(int table) const {
		return tables[table - 1];
	}

	// encontrar la primera mesa vacía
	bool checkFirstTableEmpty(int& table);

	// asignar una mesa al primer grupo de clientes
	void assignTable(int table, vector<Client*> firstGroup);

	// comprobar si algún cliente ha abandonado una mesa o si ha terminado de comer para marcarla como desocupada
	void checkTables();

	// comprobar si un cliente si un cliente está de camino a pagar o pagando
	bool isPaying(GameObject* client);

	// comprobar si algún grupo ha abandonado el local para quitarlo de la lista
	void refreshClientsGroup();

	ClientsManager(GameObject* parent, vector<_ecs::_dish_id> menu, float frequencyClients, float speedClients, int maxClients);

public:

	static constexpr _ecs::_cmp_id id = _ecs::cmp_CLIENTS_MANAGER;

	// devuelve al primero grupo de clientes que hay en la entrada esperando a ser atendido
	inline vector<Client*> getFirstEntrance() {
		return entrance.front();
	}

	// devuelve un puntero a la cola de la caja
	inline list<Client*>* getPayQueue() {
		return &pay;
	}

	// se llama cuando se quiera asignar una mesa al primer grupo de clientes
	// se le pasa la mesa que se le desea asignar
	void assignFirstGroup(int table);

	// se llama cuando se quiere cobrar a los clientes que hay en la caja registradora
	void collectAndLeave();

	// hay espacio para que vayan a la cola de la caja
	bool canOccupyPay(vector<Client*> mates);

	// se realizan todas las comprobaciones
	virtual void update();
};