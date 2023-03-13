#include "DeskComp.h"
#include "../structure/GameObject.h"
#include "../components/ClientState.h"
#include "../exceptions/CompNotFound.h"
#include "Transform.h"
#include "../objects/ClientsManager.h"
#include "../gameObjects/Client.h"
#include "../utils/checkML.h"

DeskComp::DeskComp(GameObject* parent, float width, float height, int id) : TriggerComp(parent, Vector(0, 0), width, height, DeskComp::id), sucia(false), num(id) {
	trans = parent->getComponent<Transform>();
	if (trans == nullptr) {
		throw exceptions::CompNotFound("Transform", "DeskComp");
	}
	dirtyIcon = &(SDLUtils::instance())->images().at("CLEANTABLE_ICON");
	dirtyPlate = &(SDLUtils::instance())->images().at("DIRT_PLATES");

}

void DeskComp::assignClients(const std::vector<Client*>& clients) {
	assigned = clients;
}

void DeskComp::spreadOverlap() {
	for (auto obj : assigned) {
		obj->getComponent<ClientTrigger>()->isOverlapping();
	}
}

void DeskComp::cleanDesk() {
	sucia = false;
}

bool DeskComp::isOccupied() {
	return !assigned.empty() || sucia;
}

void DeskComp::isOverlapping() {
	if (!ih->isKeyDown(SDLK_SPACE)) return;

	if (sucia) cleanDesk();
	else spreadOverlap();
}

void DeskComp::update() {
	if (!assigned.empty()) {
		ClientState::States st = assigned[0]->getComponent<ClientState>()->getState();
		// Si los clientes han terminado de comer se ensucia la mesa.
		if (st == ClientState::HAS_LEFT) {
			sucia = true;
			assigned.clear();
			// Si los clientes se han quedado sin felicidad no se ensucia la mesa.
		}
		else if (st == ClientState::OUT) {
			assigned.clear();
		}
	}
	

}

void DeskComp::render() {
	if (sucia) {
		dirtyIcon->render(build_sdlrect(trans->getPos().getX() + trans->getW() / 2 - ICON_WIDTH / 2, trans->getPos().getY() +ICON_OFFSETY, ICON_WIDTH, ICON_HEIGHT));
		dirtyPlate->render(build_sdlrect(trans->getPos().getX() + trans->getW() / 2 - PLATE_WIDTH / 2, trans->getPos().getY() + trans->getH() / 2 - PLATE_HEIGHT / 2, PLATE_WIDTH, PLATE_HEIGHT));
	}
}
