#include "KitchenTriggerComp.h"
#include "../Structure/Scene.h"
#include "Ingredients.h"
#include "../Utilities/InputHandler.h"
#include "../Utilities/checkML.h"

KitchenTriggerComp::KitchenTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	ing = parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Ingredients>();
	ih = InputHandler::instance();
}

void KitchenTriggerComp::isOverlapping() {
	if((ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_Y)) || ih->isKeyDown(SDLK_r))
		ing->removeLastIngredient();
	else if((ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) || ih->isKeyDown(SDLK_x))
		ing->removeAllIngredients();
}

void KitchenTriggerComp::onTriggerExit() {
	ing->removeAllIngredients();
}