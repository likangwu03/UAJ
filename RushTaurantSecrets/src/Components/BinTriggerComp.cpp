#include "BinTriggerComp.h"

#include "../Scenes/HUD/UIRestaurant.h"
#include "../Structure/GameManager.h"
#include "../Scenes/GameScenes/Restaurant.h"

#include "../Utilities/checkML.h"

BinTriggerComp::BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	throwDish(&sdlutils().soundEffects().at("THROW_DISH")),
	inventory(GameManager::get()->getRestaurant()->getUI()->getInventory()->getComponent<InventoryComp>()), 
	highlight(parent->getComponent<Image>())
{
	highlight->setActive(false);
};


void BinTriggerComp::isOverlapping() {
	highlight->setActive(true);
	// cleon: mejor en 1 if
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada

	if(!inventory->isEmpty()) throwDish->play();

	inventory->freeDish();
}

void BinTriggerComp::onTriggerExit() {
	highlight->setActive(false); return;
}