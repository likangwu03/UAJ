#pragma once

#include "../GameObjects/Client.h"
#include "../Structure/Manager.h"
#include "../Structure/Scene.h"
#include "../Definitions/Paths_def.h"
#include "../Utilities/checkML.h"
#include "../Utilities/RelativeToGlobal.h"
#include "../Scenes/HUD/UIRestaurant.h"
#include "../Components/ClockComponent.h"
#include <vector>
#include <array>
#include <list>
#include <algorithm>

class DeskComp;

using namespace std;

const int MAX_ENTRANCE = 3;
const int MAX_PAY = 7;

class ClientsManager : public Manager<ClientsManager> {

	// dar acceso al constructor privado a la clase Manager, de la que hereda
	friend Manager<ClientsManager>;

private:
	// para hacer cosas si eres Server
	bool active_; 
	// cola con la entrada
	list<vector<Client*>> entrance;
	// cola con la caja de pagar
	// los clientes se colocan todos en fila
	list<Client*> pay;
	// lista con los grupos de clientes
	list<vector<Client*>> clientsGroups;
	// menu del día
	vector<_ecs::DishInfo>* menu;
	Scene* scene;
	SDLUtils* sdl;
	float elapsedTime;
	float timer;
	float speed;
	int maxClients;
	// indica si el primer cliente en la entra se ha asignado o no
	bool assignedClient;
	// se utiliza para indicar si la mesas est�n ocupadas o no 
	// pasandole el grupo que se sienta en ella
	array<DeskComp*, _ecs::NUM_TABLES> tables;

	// a�adir un cliente cada cierto tiempo
	void addFrequently();

	// comprobar si la entrada est� vac�a
	inline bool isEntranceEmpty() {
		return entrance.size() == 0;
	}

	// recolar en la entrada al resto si se ha ido alg�n cliente
	void recolocateEntranceAll(std::list<vector<Client*>>::iterator it);

	// recolocar en la caja al resto si se ha ido alg�n cliente
	void recolocatePayAll(std::list<Client*>::iterator it);

	// crear un grupo de clientes
	void createGroupClients();
	// para cliente 
	void createGroupClients(const Message& message);

	// crear un cliente
	Client* createClient(int posGroup,int sprite_);

	// comprobar si alg�n cliente ha llegado a la caja registradora y a�adirlo a la cola de pagar
	// se a�aden todos los clientes, sin importar del grupo que sean, en fila
	void checkCashRegister();

	// eliminar al primer grupo de clientes si se le ha asignado una mesa
	void firstClientAssigned();

	// comprueba si un cliente no ha abandonado la entrada
	static bool notAbandonedEntrance(Client* client);

	// comprobar si un grupo de clientes de la entrada se tiene que marchar porque se queda sin felicidad
	void checkHappinessEntrance();

	// comprobar si alg�n grupo de cliente de la caja se ha quedado sin felicidad y se ha marchado
	void checkHappinessPay();

	// comprobar si una mesa est� ocupada o no
	inline bool isTableFull(int table) const {
		return tables[table - 1];
	}

	static bool deskIsNotOccupied(DeskComp* desk);

	// encontrar la primera mesa vac�a
	bool checkFirstTableEmpty(int& table);

	// asignar una mesa al primer grupo de clientes
	void assignTable(int table, vector<Client*> firstGroup, bool send=true); 

	// comprobar si un cliente si un cliente est� de camino a pagar o pagando
	bool isPaying(GameObject* client);

	static bool notOutOfLocal(Client* client);

	// comprobar si alg�n grupo ha abandonado el local para quitarlo de la lista
	void refreshClientsGroup();

	ClientsManager(GameObject* parent, vector<_ecs::_dish_id> menu, float frequencyClients, float speedClients, int maxClients);

public:

	static constexpr _ecs::_cmp_id id = _ecs::cmp_MANAGER;

	// devuelve al primero grupo de clientes que hay en la entrada esperando a ser atendido
	inline vector<Client*> getFirstEntrance() {
		return entrance.front();
	}

	// devuelve un puntero a la cola de la caja
	inline list<Client*>* getPayQueue() {
		return &pay;
	}

	// devuelve si quedan clientes en el restaurante o no
	// mejor comprobar con el grupo de clientes
	// porque de la lista de clientes se quitan cuando se están marchando del local
	inline bool noClients() const {
		return GameManager::get()->getRestaurant()->getGroup(_ecs::grp_CLIENTS)->empty();
	}

	// se llama cuando se quiera asignar una mesa al primer grupo de clientes
	// se le pasa la mesa que se le desea asignar
	void assignFirstGroup(int table);//..............................................................

	static bool notAllGroupPaying(Client* client);

	bool canCollect() const;

	// se llama cuando se quiere cobrar a los clientes que hay en la caja registradora
	void collectAndLeave();

	// hay espacio para que vayan a la cola de la caja
	bool canOccupyPay(vector<Client*> mates);

	// guarda el componente de las mesas en el array
	// no se hace en la constructora porque
	// las mesas se tienen que crear despu�s que el ClientsManager
	void initTables();

	// se realizan todas las comprobaciones
	virtual void update();

	void initComponent();

	void nextDay();

	void receive(const Message& message) override;

	void setNetActive(bool s) { active_ = s; }
};