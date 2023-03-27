#include "SuperCashRegisterTriggerComp.h"

#include "../Scenes/UIRestaurant.h"
#include "../Structure/GameManager.h"
#include "../Scenes/Restaurant.h"

#include "../Utilities/checkML.h"

SuperCashRegisterTriggerComp::SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_)
{
	highlight = parent->getComponent<Image>();
	highlight->setActive(false);
	money = GameManager::get()->getMoney();
};

void SuperCashRegisterTriggerComp::isOverlapping() {
	highlight->setActive(true);
	// cleon: mejor en 1 if
	if (ih->joysticksInitialised()) {
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
			money->subtractMoney(money->getPrize());
			money->setPrize(0);
			GameManager::get()->changeScene((Scene*)GameManager::get()->getRestaurant());
		}
	}
	else if (ih->isKeyDown(SDLK_SPACE)) {
		money->subtractMoney(money->getPrize());
		money->setPrize(0);
		GameManager::get()->changeScene((Scene*)GameManager::get()->getRestaurant());
	}
}

void SuperCashRegisterTriggerComp::onTriggerExit() {
	highlight->setActive(false); return;
}