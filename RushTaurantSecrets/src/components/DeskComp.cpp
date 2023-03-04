#include "DeskComp.h"
#include "../structure/GameObject.h"
#include "../components/ClientState.h"
#include "../exceptions/CompNotFound.h"
#include "Transform.h"
#include "../objects/ClientsManager.h"
#include "../utils/checkML.h"

DeskComp::DeskComp(GameObject* parent) : TriggerComp(parent, Vector(), 10, 10), sucia(false), num(0) {
	trans = parent->getComponent<Transform>();
	if(trans == nullptr) {
		throw exceptions::CompNotFound("Transform", "DeskComp");
	}
}

bool DeskComp::assignClients() {
	/*
	if(!assigned.empty() || sucia) return false;
	GameObject* client = ClientsManager::get()->getFirstEntrance();
	if(client->getComponent<ClientTrigger>()->isSelected()) {
		assigned.push_back(client);
		ClientsManager::get()->assignFirstClient(num);
		return true;
	}
	*/
	return false;
}

void DeskComp::spreadOverlap() {
	for(auto it = assigned.begin(); it != assigned.end(); ++it) { // cleon: regreso al futuro con los iteradores.
		(*it)->getComponent<ClientTrigger>()->isOverlapping();
	}
}

void DeskComp::leaveDesk() {
	sucia = true;
	assigned.clear();
}

void DeskComp::cleanDesk() {
	sucia = false;
}

void DeskComp::isOverlapping() {
	if(!ih->isKeyDown(SDLK_SPACE)) return;

	if(sucia) cleanDesk();
	else if(assigned.empty()) assignClients();
	else spreadOverlap();
}