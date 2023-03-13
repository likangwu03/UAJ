#include "goToPantryTrigger.h"

#include "../sdlutils/InputHandler.h"
#include "../structure/GameManager.h"
#include "../utils/checkML.h"

goToPantryTrigger::goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) { };

void goToPantryTrigger::onTriggerEnter() {
	if(ih->isKeyDown(SDLK_SPACE))
		GameManager::instance()->changeScene(GameManager::instance()->getRestaurant());
}
