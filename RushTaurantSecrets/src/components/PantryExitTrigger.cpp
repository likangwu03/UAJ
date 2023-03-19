#include "PantryExitTrigger.h"

#include "../structure/GameManager.h"
#include "../structure/Scene.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"

#include "../utils/checkML.h"

PantryExitTrigger::PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_), parent(parent) {
	ih = InputHandler::instance();
};


void PantryExitTrigger::isOverlapping() {
	if (ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getRestaurant());
		GameManager::get()->getCurrentScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setPos(Vector(640, 130));
	}
}
