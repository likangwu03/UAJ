#include "DeskComp.h"
#include "../Structure/GameObject.h"
#include "ClientState.h"
#include "../Exceptions/CompNotFound.h"
#include "Transform.h"
#include "../Managers/ClientsManager.h"
#include "../GameObjects/Client.h"
#include "../Utilities/checkML.h"
#include "../Structure/Game.h"

DeskComp::DeskComp(GameObject* parent, float width, float height, int id) :
	TriggerComp(parent, Vector(0, 0), width, height, DeskComp::id),
	dirty(false), num(id),
	inventory(GameManager::get()->getRestaurant()->getUI()->getInventory()->getComponent<InventoryComp>()),
	cleanSound(&sdlutils().soundEffects().at("CLEAN_TABLE")),
	assignSound(&sdlutils().soundEffects().at("ASSIGN_TABLE"))
{
	assignSound->setVolume(10);
	trans = parent->getComponent<Transform>();
	if (trans == nullptr) {
		throw exceptions::CompNotFound("Transform", "DeskComp");
	}
	dirtyIcon = &(SDLUtils::instance())->images().at("CLEANTABLE_ICON");
	dirtyPlate = &(SDLUtils::instance())->images().at("DIRT_PLATES");

}

void DeskComp::assignClients(const std::vector<Client*>& clients) {
	assignSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
	assignSound->play();
	assigned = clients;
}

void DeskComp::serveTable() {
	for (auto client : assigned) {
		ClientState* clientState = client->getComponent<ClientState>();
		switch (clientState->getState()) {
		case ClientState::TAKEMYORDER:
			clientState->takeOrder();
			break;
		case ClientState::ORDERED:
			if (inventory->serveDish(clientState->getOrderedDish())) {
				clientState->getServed();
			}
			break;
		}
	}
}

void DeskComp::cleanDesk(bool send) {
	dirty = false;
	cleanSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
	cleanSound->play();
	if (send) {
		Message m;
		m.id = Message::msg_CLEAN_DESK;
		m.desk.id = getID();
		Game::get()->getCoopHandler()->send(m);
	}
}

bool DeskComp::isOccupied() {
	return !assigned.empty() || dirty;
}

void DeskComp::isOverlapping() {
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B))
			return;
	}		
	else if (!ih->isKeyDown(SDLK_SPACE)) return;

	if (dirty) cleanDesk();
	else serveTable();//spreadOverlap();
}

void DeskComp::update() {
	if (!assigned.empty()) {
		ClientState::States st = assigned[0]->getComponent<ClientState>()->getState();
		// Si los clientes han terminado de comer se endirty la mesa.
		if (st == ClientState::HAS_LEFT) {
			dirty = true;
			assigned.clear();
			// Si los clientes se han quedado sin felicidad no se endirty la mesa.
		}
		else if (st == ClientState::OUT)
			assigned.clear();
	}
}

void DeskComp::render() {
	if (dirty) {
		dirtyIcon->render(build_sdlrect(trans->getPos().getX() + trans->getW() / 2 - ICON_WIDTH / 2, trans->getPos().getY() +ICON_OFFSETY, ICON_WIDTH, ICON_HEIGHT));
		dirtyPlate->render(build_sdlrect(trans->getPos().getX() + trans->getW() / 2 - PLATE_WIDTH / 2, trans->getPos().getY() + trans->getH() / 2 - PLATE_HEIGHT / 2, PLATE_WIDTH, PLATE_HEIGHT));
	}
}
void DeskComp::receive(const Message& message) {
	if (message.id == Message::msg_CLEAN_DESK && message.desk.id == num) {
		cleanDesk(false);
	}
}

void DeskComp::nextDay() {
	assigned.clear();
	dirty = false;
}
