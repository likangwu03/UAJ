#include "SuperCashRegisterTriggerComp.h"

#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "../scenes/Restaurant.h"

#include "../utils/checkML.h"

SuperCashRegisterTriggerComp::SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_)
{
	highlight = parent->getComponent<Image>();

	highlight->setActive(false);
};


void SuperCashRegisterTriggerComp::isOverlapping() {
	highlight->setActive(true);
	// cleon: mejor en 1 if
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada

}

void SuperCashRegisterTriggerComp::onTriggerExit() {
	highlight->setActive(false); return;
}