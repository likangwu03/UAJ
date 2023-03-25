#include "goToPantryTrigger.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/GameManager.h"
#include "../Structure/Scene.h"
#include "../Structure/GameObject.h"
#include "Transform.h"
#include "../Utilities/checkML.h"

goToPantryTrigger::goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) { };

void goToPantryTrigger::isOverlapping() {
	if (ih->isKeyDown(SDLK_SPACE) || (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A))) {
		parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->setActives(false);
		Scene* pantry = (Scene*)GameManager::get()->getPantry();
		pantry->getGameObject(_ecs::hdr_PLAYER)->setActives(true);
		pantry->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setPos(Vector(800, 580));
		pantry->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setOrientation(north);
		GameManager::get()->changeScene((Scene*)GameManager::get()->getPantry());
	}
	
}
