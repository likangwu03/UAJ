#include "BinTriggerComp.h"
#include "../scenes/UIRestaurant.h"

#include "../utils/checkML.h"

BinTriggerComp::BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	inventory(static_cast<UIRestaurant*>(parent->getScene()->getUI())->getInventory()->getComponent<InventoryComp>()) { };


void BinTriggerComp::isOverlapping() {
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada
	//temporal, no comprueba si esta el plato que quiere, solo comprueba que el jugador tenga platos
	if (inventory->freeSpace() != 0) 
		inventory->freeDish();
}