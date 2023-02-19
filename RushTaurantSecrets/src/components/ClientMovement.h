#pragma once
#include "../structure/Paths_def.h"
#include "../structure/GameObject.h"
#include "../structure/Component.h"
#include "../components/StraightMovement.h"
#include "../components/ClientState.h"
#include "../components/Transform.h"

using namespace std;

class ClientMovement : public Component {
private:
	ClientState* clientState;
	StraightMovement* straightMovement;
	Transform* transform;
	int assignedTable;
	int posEntrance;
	int posPay;

	Route tableRoute(string type) {
		string aux = type + "_TABLE_" + std::to_string(this->assignedTable);
		auto it = _ecs::stringToEnum.find(aux);
		if (it != stringToEnum.end()) {
			return paths[it->second];
		}
	}

	void colocateEntrance() const {
		// se calcula el camino
		Vector entrance = _ecs::ENTRY;
		// dependiendo de la pos en la entrada donde esté se coloca en un lugar o en otro
		entrance.setX(entrance.getX() + transform->getW() * posEntrance);
		// se mueve
		straightMovement->addPath(vector<Vector>{entrance});
	}

	void colocateCashRegister() {
		vector<Vector> payPath = tableRoute("PAY").points;
		straightMovement->addPath(payPath);
		outTable();
	}

	void colocatePay() {
		// se obtiene la primera posición
		Vector posRegister = _ecs::CASH_REGISTER;
		// se calcula a partir de ella la pos que le corresponde en la cola
		posRegister.setX(posRegister.getX() + transform->getW() * posPay);
		// se mueve
		straightMovement->addPath(vector<Vector>{posRegister});
		/*
		// se calcula el camino
		vector<Vector> payPath = tableRoute("PAY").points;
		Vector posRegister = _ecs::CASH_REGISTER;
		// dependiendo de la pos en la caja donde esté se coloca en un lugar o en otro
		posRegister.setX(posRegister.getX() + transform->getW() * posPay);
		payPath[payPath.size() - 1] = posRegister;
		// se mueve
		straightMovement->addPath(payPath, SPEED);
		*/
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

	// ha abandonado la cola de pagar sin pagar
	void abandonPay() {
		// se calcula el camino de salida
		float yExit = _ecs::OUT.getY();
		// se calcula el primer punto
		Vector firstPoint = Vector(transform->getPos().getX(), yExit);
		vector<Vector> leave;
		leave.push_back(firstPoint);
		// se añade el punto de afuera
		leave.push_back(_ecs::OUT);
		straightMovement->addPath(leave);
	}

	// el cliente está quieto
	// se establece su nuevo, su orientación y la animación a ejecutar
	void stationary(ClientState::States state, GOOrientation orientation, movementState mov) {
		clientState->setState(state);
		transform->setOrientation(orientation);
		transform->setMovState(mov);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENT_MOVEMENT;

	ClientMovement(GameObject* parent, int posEntrance) : Component(parent, id), assignedTable(-1), posEntrance(posEntrance), posPay(-1) {
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
		// avanza una posición
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

	void payAndLeave() {
		outPay();
		clientState->setState(ClientState::OUT);
		straightMovement->addPath(_ecs::paths[_ecs::PAY_AND_LEAVE].points);
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
			}
			break;
		case ClientState::FINISH_EAT:
			// colocatePay();
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
				straightMovement->addPath(vector<Vector>{_ecs::OUT});
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