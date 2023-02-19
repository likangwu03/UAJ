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
	SDLUtils* sdl;
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

	void colocateEntrance() {
		Vector entrance = _ecs::ENTRY;
		// se calcula a partir de su pos en la cola de entrada
		entrance.setX(entrance.getX() + posEntrance);
		// se mueve
		straightMovement->addPath(vector<Vector>{entrance});
	}

	void colocateCashRegister() {
		vector<Vector> payPath = tableRoute("PAY").points;
		straightMovement->addPath(payPath);
		outTable();
	}

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
		int fh = sdl->height() / 20;

		// se calcula el camino de salida
		vector<Vector> leave;

		// primer punto
		int fWidth = sdl->width() / 40;
		int xExit = transform->getPos().getX() / fWidth;
		int yExit = _ecs::OUT.getY();
		Vector firstPoint = Vector(xExit, yExit);
		leave.push_back(firstPoint);

		// se añade el punto de afuera
		leave.push_back(_ecs::OUT);

		straightMovement->addPath(leave);
	}

	// el cliente está quieto
	// se establece su nuevo estado, su orientación y la animación a ejecutar
	void stationary(ClientState::States state, GOOrientation orientation, movementState mov) {
		clientState->setState(state);
		transform->setOrientation(orientation);
		transform->setMovState(mov);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENT_MOVEMENT;

	ClientMovement(GameObject* parent, int posEntrance) : Component(parent, id), assignedTable(-1), posEntrance(posEntrance), posPay(-1) {
		sdl = SDLUtils::instance();
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