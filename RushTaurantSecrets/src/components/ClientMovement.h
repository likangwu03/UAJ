#pragma once
#include "../structure/Paths_def.h"
#include "../components/StraightMovement.h"
#include "../components/ClientState.h"
#include "../components/Transform.h"
#include "../components/ClientStateRender.h"
#include "../structure/GameObject.h"
#include "../structure/Component.h"

using namespace std;

class ClientsManager;

class ClientMovement : public Component {
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

	// devuelve una ruta desde la entrada hasta la mesa
	Route tableRoute(string type);

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

	// se establece su nuevo estado, su orientación y la animación a ejecutar
	void stationary(ClientState::States state, GOOrientation orientation, movementState mov);

public:

	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ClientMovement(GameObject* parent, int posEntrance);

	// recolocarse en la entrada si alguien se ha marchado
	void recolocateEntrance();

	// pos en la cola de pagar
	void setPosPay(int pos) {
		this->posPay = pos;
	}

	// recolocarse en la cola de pagar si alguien se ha marchado
	void recolotatePay();

	// asignar mesa
	void assignTable(int assignedTable);

	// paga por su comida y se marcha
	void payAndLeave();

	bool hasAbandonedEntrance() const {
		if (clientState->getState() == ClientState::OUT) {
			if (posEntrance != -1) {
				return true;
			}
		}
		return false;
	}

	bool hasAbandonedPay() const {
		return clientState->getState() == ClientState::OUT && posPay != -1;
	}

	// abandona la mesa porque se queda sin felicidad
	bool hasAbandonedTable() const {
		return clientState->getState() == ClientState::OUT && assignedTable != -1;
	}

	// abadona la mesa porque ha terminado de comer y puede ir a la caja
	bool hasFinishedEating() const;

	int getAssignedTable() const {
		return assignedTable;
	}

	void update();
};