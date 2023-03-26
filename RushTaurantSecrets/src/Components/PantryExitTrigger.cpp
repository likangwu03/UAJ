#include "PantryExitTrigger.h"

#include "../Structure/GameManager.h"
#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "Transform.h"
#include "../Scenes/Restaurant.h"

#include "../Utilities/checkML.h"

PantryExitTrigger::PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_), parent(parent) {
	ih = InputHandler::instance();
};


void PantryExitTrigger::isOverlapping() {
	if (ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) {
		parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->setActives(false);
		GameManager::get()->changeScene(GameManager::get()->getRestaurant());
		GameManager::get()->getCurrentScene()->getGameObject(_ecs::hdr_PLAYER)->setActives(true);
		GameManager::get()->getCurrentScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setPos(Vector(640, 130));
		GameManager::get()->getCurrentScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setOrientation(south);
	}
}
