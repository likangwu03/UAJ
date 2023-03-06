#pragma once
#include "../structure/Paths_def.h"
#include "../components/StraightMovement.h"
#include "../components/ClientState.h"
#include "../components/Transform.h"
#include "../components/ClientStateRender.h"
#include "../structure/GameObject.h"
#include "../structure/Component.h"
#include "../utils/checkML.h"
#include <vector>

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

	// comprobar si todos los integrantes del grupo han terminado de comeer
	bool hasEveryoneEaten() const;

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

	// ha abandonado la cola de la caja sin pagar
	void abandonPay();

	// ha abandonado la cola de entrada por perder felicidad
	void abandonEntrance();

	// se establece su nuevo estado, su orientación y la animación a ejecutar
	void stationary(ClientState::States state, GOOrientation orientation, movementState mov);

public:

	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ClientMovement(GameObject* parent, int posEntrance, int posGroup);

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

	inline bool hasAbandonedEntrance() const {
		return clientState->getState() == ClientState::OUT && posEntrance != -1;
	}

	inline bool hasAbandonedPay() const {
		return clientState->getState() == ClientState::OUT && posPay != -1;
	}

	// abandona la mesa porque se queda sin felicidad
	inline bool hasAbandonedTable() const {
		return clientState->getState() == ClientState::OUT && assignedTable != -1;
	}

	inline int getAssignedTable() const {
		return assignedTable;
	}

	// pasar el grupo de clientes al que pertence
	inline void setGroup(vector<Client*> mates) {
		this->mates = mates;
	}

	virtual void update();
};