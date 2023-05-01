#pragma once
#include "../Definitions/Paths_def.h"
#include "StraightMovement.h"
#include "ClientState.h"
#include "Transform.h"
#include "ClientStateRender.h"
#include "../Structure/GameObject.h"
#include "../Structure/Component.h"
#include "../Utilities/checkML.h"
#include <vector>
#include <algorithm>

using namespace std;

class ClientsManager;
class Client;

class ClientMovement : public Component {
	enum typePath {ARRIVE, PAY, OUT};

private:

	ClientState* clientState;
	StraightMovement* straightMovement;
	Transform* transform;
	SDLUtils* sdl;
	int assignedTable;
	int posEntrance;
	int posPay;
	ClientStateRender* render;
	ClientsManager* clientsManager;
	vector<Client*> mates;
	int posGroup;
	// colocado en la cola de pagar, es decir, est?quieto
	bool placedPay;
	SoundEffect* arriveSound;
	SoundEffect* finishEatingSound;


	void addPath(const vector<Vector>& points);

	// función que se utiliza para el find que se hace en la función de más abajo
	// tienen que ser siempre estáticas
	// se comprueba si un cliente no ha terminado de comer
	static bool hasNotEaten(Client* mate);

	// comprobar si todos los integrantes del grupo han terminado de comer
	bool hasEveryoneEaten() const;

	static bool isNotSit(Client* mate);

	// comprobar si todos los integrantes del grupo están sentados
	bool isEveryoneSit() const;

	// se comprueba si un cliente no est?en la cola esperando a pagar
	static bool isNotPaying(Client* mate);

	// se comprueba si alguno de sus compañero se ha marchado para que él también se vaya
	void goOut(ClientState::States currentState);

	// devuelve una ruta
	inline Route tableRoute(typePath type) const {
		// posGroup = 0 -> LEFT
		// posGroup = 1 -> RIGHT
		// posGroup = 2 -> UP
		// posGroup = 3 -> DOWN
		_path_client_id path = _ecs::enumClientPaths[assignedTable - 1][posGroup][type];
		return clientsPaths[path];
	}

	// llega al restaurante y se coloca en la entrada
	void colocateEntrance();

	// desde la mesa hasta la caja registradora
	void colocateCashRegister();

	// desde la caja registradora hasta la posición que le corresponde en la cola de pagar
	void colocatePay();

	// ha abandonado la entrada
	inline void outEntrance() {
		posEntrance = -1;
	}

	// ha abandonado la mesa
	inline void outTable() {
		assignedTable = -1;
	}

	// ha abandonado la cola de pagar
	inline void outPay() {
		posPay = -1;
	}

	inline bool isPlacedPay() const {
		return placedPay;
	}

	// ha abandonado la cola de la caja sin pagar
	void abandonPay();

	// ha abandonado la cola de entrada por perder felicidad
	void abandonEntrance();

public:

	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ClientMovement(GameObject* parent, int posEntrance, int posGroup);

	// no se inicializa en la constructora porque
	// ClientMovement tiene que ejecutarse antes que ClientState,
	// pero ClientState se crea después que ClientMovement
	virtual void initState();

	// recolocarse en la entrada si alguien se ha marchado
	void recolocateEntrance();

	// pos en la cola de pagar
	inline void setPosPay(int pos) {
		this->posPay = pos;
	}

	// recolocarse en la cola de pagar si alguien se ha marchado
	void recolotatePay();

	// asignar mesa
	void assignTable(int assignedTable);

	// paga por su comida y se marcha
	void payAndLeave();

	// comprobar si todos los integrantes del grupo están en la cola esperando a pagar
	bool isEveryonePaying() const;

	inline bool hasAbandonedEntrance() const {
		return clientState->getState() == ClientState::OUT && posEntrance != -1;
	}

	inline bool hasAbandonedPay() const {
		return clientState->getState() == ClientState::OUT && posPay != -1;
	}

	inline int getAssignedTable() const {
		return assignedTable;
	}

	// pasar el grupo de clientes al que pertence
	inline void setGroup(vector<Client*> mates) {
		this->mates = mates;
	}


	virtual void update();

	int getAssignedTable() { return assignedTable; }
	int getPosGroup() { return posGroup; }
};