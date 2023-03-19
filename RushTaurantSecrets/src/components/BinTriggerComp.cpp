#include "BinTriggerComp.h"

#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "../scenes/Restaurant.h"

#include "../utils/checkML.h"

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

	//temporal, no comprueba si esta el plato que quiere, solo comprueba que el jugador tenga platos
	if (inventory->freeSpace() != 0) 
		inventory->freeDish();

}
void BinTriggerComp::onTriggerExit() {
	highlight->setActive(false); return;
}