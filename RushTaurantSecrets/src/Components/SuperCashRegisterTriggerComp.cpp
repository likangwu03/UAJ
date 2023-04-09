#include "SuperCashRegisterTriggerComp.h"

#include "../Scenes/UIRestaurant.h"
#include "../Structure/GameManager.h"
#include "../Scenes/Restaurant.h"
#include "../Components/ShoppingMenuComp.h"
#include "../Scenes/SuperMarket.h"


#include "../Utilities/checkML.h"

SuperCashRegisterTriggerComp::SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), sdl(SDLUtils::instance()), restaurantMusic(&sdl->musics().at("RESTAURANT_MUSIC"))
{
	highlight = parent->getComponent<Image>();
	highlight->setActive(false);
	money = GameManager::get()->getMoney();
};

void SuperCashRegisterTriggerComp::isOverlapping() {
	highlight->setActive(true);

	if (bM == nullptr) {
		bM = dynamic_cast<SuperMarket*>(parent->getScene())->getBM();
		bMC = bM->getComponent<BasketMarketComponent>();
		if (!bMC->getBasketON())
			bMC->setBasketON(true);
	}

	// cleon: mejor en 1 if
	if (ih->joysticksInitialised()) {
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
			money->subtractMoney(money->getPrize());
			money->setPrize(0);
			payAndLeave();
		}
	}
 	else if (ih->isKeyDown(SDLK_SPACE)) {
		money->subtractMoney(money->getPrize());
		money->setPrize(0);
		payAndLeave();
	}
}

void SuperCashRegisterTriggerComp::onTriggerExit() {
	highlight->setActive(false);
	bMC->setBasketON(false);
	bM = nullptr;
	bMC = nullptr;
}

void SuperCashRegisterTriggerComp::payAndLeave() {
	vector<pair<_ecs::_ingredients_id, int>> ing;
	ing = GameManager::get()->getSupermarket()->getUI()->getGameObject(hdr_SM_INVENTORY)->getComponent<BasketMarketComponent>()->getIngredients();
	GameManager::get()->setIngredients(ing);
	GameManager::get()->getRestaurant()->reset();
	GameManager::get()->changeScene((Scene*)GameManager::get()->getRestaurant());
	restaurantMusic->play();
}
