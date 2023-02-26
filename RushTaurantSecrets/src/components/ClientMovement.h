#pragma once
#include "../structure/Paths_def.h"
#include "../structure/GameObject.h"
#include "../structure/Component.h"
#include "../components/StraightMovement.h"
#include "../components/ClientState.h"
#include "../components/Transform.h"
#include "../components/ClientStateRender.h"

using namespace std;

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

	// devuelve una ruta desde la entrada hasta la mesa
	Route tableRoute(string type) {
		string aux = type + "_TABLE_" + std::to_string(this->assignedTable);
		auto it = _ecs::stringToEnum.find(aux);
		if (it != stringToEnum.end()) {
			return paths[it->second];
		}
	}

	// llega al restaurante y se coloca en la entrada
	void colocateEntrance() {
		Vector entrance = _ecs::ENTRY;
		// se calcula a partir de su pos en la cola de entrada
		entrance.setX(entrance.getX() + posEntrance);
		// se mueve
		straightMovement->addPath(vector<Vector>{entrance});
	}

	// desde la mesa hasta la caja registradora
	void colocateCashRegister() {
		vector<Vector> payPath = tableRoute("PAY").points;
		straightMovement->addPath(payPath);
		outTable();
	}

	// desde la caja registradora hasta la posición que le corresponde en la cola de pagar
	void colocatePay() {
		Vector posRegister = _ecs::CASH_REGISTER;
		// se calcula a partir de su pos en la cola de la caja
		posRegister.setX(posRegister.getX() + posPay);
		// se mueve
		straightMovement->addPath(vector<Vector>{posRegister});
	}

	// ha abandonado la entrada
	void outEntrance() {
		posEntrance = -1;
	}

	// ha abandonado la mesa
	void outTable() {
		assignedTable = -1;
	}

	// ha abandonado la cola de pagar
	void outPay() {
		posPay = -1;
	}

	// ha abandonado la cola de la caja sin pagar
	void abandonPay() {
		// se calcula el camino de salida
		vector<Vector> leave;

		// primer punto
		int fWidth = sdl->width() / 40;
		int xExit = transform->getPos().getX() / fWidth;
		int yExit = _ecs::OUT_PAY.getY();
		Vector firstPoint = Vector(xExit, yExit);
		leave.push_back(firstPoint);

		// se añade el punto de afuera
		leave.push_back(_ecs::OUT_PAY);

		straightMovement->addPath(leave);
	}

	// se establece su nuevo estado, su orientación y la animación a ejecutar
	void stationary(ClientState::States state, GOOrientation orientation, movementState mov) {
		clientState->setState(state);
		transform->setOrientation(orientation);
		transform->setMovState(mov);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_MOVEMENT;

	ClientMovement(GameObject* parent, int posEntrance) : Component(parent, id), assignedTable(-1), posEntrance(posEntrance), posPay(-1) {
		sdl = SDLUtils::instance();
		render=parent->getComponent<ClientStateRender>();
		clientState = parent->getComponent<ClientState>();
		straightMovement = parent->getComponent<StraightMovement>();
		transform = parent->getComponent<Transform>();

		colocateEntrance();
	}

	// recolocarse en la entrada si alguien se ha marchado
	void recolocateEntrance() {
		--posEntrance;
		colocateEntrance();
	}

	// pos en la cola de pagar
	void setPosPay(int pos) {
		this->posPay = pos;
	}

	// recolocarse en la cola de pagar si alguien se ha marchado
	void recolotatePay() {
		--posPay;
		colocatePay();
	}

	// asignar mesa
	void assignTable(int assignedTable) {
		this->assignedTable = assignedTable;
		straightMovement->addPath(tableRoute("ARRIVE").points);
		outEntrance();
		clientState->setState(ClientState::ASSIGNED);
	}

	// paga por su comida y se marcha
	void payAndLeave() {
		clientState->setState(ClientState::OUT);
		straightMovement->addPath(_ecs::paths[_ecs::PAY_AND_LEAVE].points);
		outPay();
	}

	bool hasAbandonedEntrance() const {
		return clientState->getState() == ClientState::OUT && posEntrance != -1;
	}

	bool hasAbandonedPay() const {
		return clientState->getState() == ClientState::OUT && posPay != -1;
	}

	bool hasAbandonedTable() const {
		return clientState->getState() == ClientState::OUT && assignedTable != -1;
	}

	int getAssignedTable() const {
		return assignedTable;
	}

	void update() {
		ClientState::States currentState;
		currentState = clientState->getState();
		switch (currentState) {
		case ClientState::START:
			if (straightMovement->hasFinishedPath()) {
				stationary(ClientState::ENTRANCE, west, idle);
			}
			break;
		case ClientState::ENTRANCE:
			// hacer que al recolocarse se active la animación idle
			if (straightMovement->hasFinishedPath()) {
				transform->setMovState(idle);
			}
			break;
		case ClientState::ASSIGNED:
			if (straightMovement->hasFinishedPath()) {
				stationary(ClientState::THINKING, tableRoute("ARRIVE").orientation, sitting);
				// para que renderice el estado de pensar
				render->renderThinkingState();
			}
			break;
		case ClientState::FINISH_EAT:
			colocateCashRegister();
			clientState->setState(ClientState::REGISTER);
			break;
		case ClientState::REGISTER:
			if (straightMovement->hasFinishedPath()) {
				clientState->setState(ClientState::CASH_REGISTER);
			}
			break;
		case ClientState::CASH_REGISTER:
			if (posPay != -1) {
				colocatePay();
				clientState->setState(ClientState::PAYING);
			}
			break;
		case ClientState::PAYING:
			if (straightMovement->hasFinishedPath()) {
				transform->setOrientation(west);
				transform->setMovState(idle);
			}
			break;
		case ClientState::OUT:
			if (posEntrance != -1) {
				straightMovement->addPath(vector<Vector>{_ecs::OUT_ENTRY});
				outEntrance();
			}
			else if (assignedTable != -1) {
				straightMovement->addPath(tableRoute("OUT").points);
				outTable();
			}
			else if (posPay != -1) {
				abandonPay();
				outPay();
			}
			if (straightMovement->hasFinishedPath()) {
				parent->setAlive(false);
			}
			break;
		}
	}
};