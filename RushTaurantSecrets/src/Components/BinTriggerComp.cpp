#include "BinTriggerComp.h"

#include "../Scenes/UIRestaurant.h"
#include "../Structure/GameManager.h"
#include "../Scenes/Restaurant.h"

#include "../Utilities/checkML.h"

BinTriggerComp::BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	inventory(GameManager::get()->getRestaurant()->getUI()->getInventory()->getComponent<InventoryComp>()), highlight(parent->getComponent<Image>())
{
	highlight->setActive(false);
};


void BinTriggerComp::isOverlapping() {
	highlight->setActive(true);
	// cleon: mejor en 1 if
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada

	inventory->freeDish();

}
void BinTriggerComp::onTriggerExit() {
	highlight->setActive(false); return;
}