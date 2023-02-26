#include "ClientMovement.h"
#include "../objects/ClientsManager.h"

// devuelve una ruta desde la entrada hasta la mesa
Route ClientMovement::tableRoute(string type) {
	std::string aux = type + "_TABLE_" + std::to_string(this->assignedTable);
	auto it = _ecs::stringToEnum.find(aux);
	if (it != _ecs::stringToEnum.end()) {
		return paths[it->second];
	}
}

// llega al restaurante y se coloca en la entrada
void ClientMovement::colocateEntrance() {
	Vector entrance = _ecs::ENTRY;
	// se calcula a partir de su pos en la cola de entrada
	entrance.setX(entrance.getX() + posEntrance);
	// se mueve
	straightMovement->addPath(vector<Vector>{entrance});
}

// desde la mesa hasta la caja registradora
void ClientMovement::colocateCashRegister() {
	vector<Vector> payPath = tableRoute("PAY").points;
	straightMovement->addPath(payPath);
	outTable();
}

// desde la caja registradora hasta la posición que le corresponde en la cola de pagar
void ClientMovement::colocatePay() {
	Vector posRegister = _ecs::CASH_REGISTER;
	// se calcula a partir de su pos en la cola de la caja
	posRegister.setX(posRegister.getX() + posPay);
	// se mueve
	straightMovement->addPath(vector<Vector>{posRegister});
}

// ha abandonado la cola de la caja sin pagar
void ClientMovement::abandonPay() {
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
void ClientMovement::stationary(ClientState::States state, GOOrientation orientation, movementState mov) {
	clientState->setState(state);
	transform->setOrientation(orientation);
	transform->setMovState(mov);
}

ClientMovement::ClientMovement(GameObject* parent, int posEntrance) :
	Component(parent, id), assignedTable(-1), posEntrance(posEntrance), posPay(-1) {
	sdl = SDLUtils::instance();
	render = parent->getComponent<ClientStateRender>();
	clientState = parent->getComponent<ClientState>();
	straightMovement = parent->getComponent<StraightMovement>();
	transform = parent->getComponent<Transform>();
	clientsManager = ClientsManager::get();

	colocateEntrance();
}

// recolocarse en la entrada si alguien se ha marchado
void ClientMovement::recolocateEntrance() {
	--posEntrance;
	colocateEntrance();
}

// recolocarse en la cola de pagar si alguien se ha marchado
void ClientMovement::recolotatePay() {
	--posPay;
	colocatePay();
}

// asignar mesa
void ClientMovement::assignTable(int assignedTable) {
	this->assignedTable = assignedTable;
	straightMovement->addPath(tableRoute("ARRIVE").points);
	outEntrance();
	clientState->setState(ClientState::ASSIGNED);
}

// paga por su comida y se marcha
void ClientMovement::payAndLeave() {
	clientState->setState(ClientState::OUT);
	straightMovement->addPath(_ecs::paths[_ecs::PAY_AND_LEAVE].points);
	outPay();
}

bool ClientMovement::hasFinishedEating() const {
	return clientState->getState() == ClientState::FINISH_EAT && clientsManager->canOccupyPay();
}

void ClientMovement::update() {
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
		// se comprueba si puede ir a la cola de pagar
		if (clientsManager->canOccupyPay()) {
			colocateCashRegister();
			clientState->setState(ClientState::REGISTER);
		}
		// sino, se pone en espera
		else {
			clientState->setState(ClientState::WAITING);
		}
		break;
	// está esperando a ir a la cola de pagar
	// se hace en dos estados para tener una doble comprobación de si puede ir
	// ya que hay un momento en el que el cliente ha llegado a la caja registradora,
	// pero no está añadido a la cola de pagar (por el orden de ejecución de los componentes)
	case ClientState::WAITING:
		if (clientsManager->canOccupyPay()) {
			clientState->setState(ClientState::FINISH_EAT);
		}
		break;
	case ClientState::REGISTER:
		if (straightMovement->hasFinishedPath()) {
			clientState->setState(ClientState::CASH_REGISTER);
		}
		break;
	case ClientState::CASH_REGISTER:
		// hasta que no se le ha asignado una posición en la caja no se mueve hasta ella
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