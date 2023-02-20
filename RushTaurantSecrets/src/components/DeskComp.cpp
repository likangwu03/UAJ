#include "DeskComp.h"
#include "../structure/GameObject.h"
#include "../components/ClientState.h"
#include "../exceptions/CompNotFound.h"
#include "Transform.h"

DeskComp::DeskComp(GameObject* parent) : Component(parent, id) {
	trans = parent->getComponent<Transform>();
	if(trans == nullptr) {
		throw exceptions::CompNotFound("Transform", "DeskComp");
	}
}

bool DeskComp::assignClients(GameObject* first, GameObject* second, GameObject* third, GameObject* fourth) {
	if(!assigned.empty()) return false;

	assigned.push_back(first);
	first->getComponent<ClientState>()->setState(ClientState::ASSIGNED);
	if(second != nullptr) {
		assigned.push_back(second);
		second->getComponent<ClientState>()->setState(ClientState::ASSIGNED);
		if(third != nullptr) {
			assigned.push_back(third);
			third->getComponent<ClientState>()->setState(ClientState::ASSIGNED);
			if(fourth != nullptr) {
				assigned.push_back(fourth);
				fourth->getComponent<ClientState>()->setState(ClientState::ASSIGNED);
			}
		}
	}
	return true;
}

bool DeskComp::receiveDish(GameObject* dish) {
	auto it = assigned.begin();
	bool served = false;
	while(it != assigned.end() && !served) {
		// Recorrer todos los clientes asignados a la mesa para comprobar si alguien ha pedido el plato y si se lo lleva.
	}
	return served;
}