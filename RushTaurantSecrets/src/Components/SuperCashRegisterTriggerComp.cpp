#include "SuperCashRegisterTriggerComp.h"

#include "../Scenes/HUD/UIRestaurant.h"
#include "../Structure/GameManager.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include "../Components/ShoppingMenuComp.h"
#include "../Scenes/GameScenes/SuperMarket.h"
#include "../Structure/Game.h"

#include "../Utilities/checkML.h"

SuperCashRegisterTriggerComp::SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), sdl(SDLUtils::instance()), restaurantMusic(&sdl->musics().at("RESTAURANT_MUSIC"))
{
	highlight = parent->getComponent<Image>();
	highlight->setActive(false);
	money = GameManager::get()->getMoney();
	restaurantMusic->setMusicVolume(GameManager::instance()->getMasterVolume());

};

void SuperCashRegisterTriggerComp::isOverlapping() {
	highlight->setActive(true);

	auto scene = dynamic_cast<SuperMarket*>(parent->getScene());
	if (bM == nullptr) {
		bM = scene->getBM();
		bMC = bM->getComponent<BasketMarketComponent>();
		if (!bMC->getBasketON()) 
			bMC->setBasketON(true);
		
		buybutton = scene->buyButton();
		buybutton->setActives(true);
		buybutton->getComponent<ButtonComp>()->setHighlighted(true);

		bMC->enterRegister(true);

	}

	if (scene->getBuy() && (money->getMoney() - money->getPrice() >= 0)) {
		scene->setBuy(false);
		
		//sendToClien();
		money->subtractMoney(money->getPrice());
		money->setPrice(0);
		buybutton->setActives(false);
		scene->getGameObject(_ecs::hdr_PLAYER)->getComponent<PlayerMovementController>()->setActive(false);
		GameManager::get()->testEnd = true;

		//payAndLeave();

	}
}

void SuperCashRegisterTriggerComp::onTriggerExit() {
	highlight->setActive(false);
	bMC->enterRegister(false);
	bMC->setBasketON(false);
	bM = nullptr;
	bMC = nullptr;

	buybutton->getComponent<ButtonComp>()->setHighlighted(false);
	buybutton->setActives(false);
	buybutton = nullptr;
}

void SuperCashRegisterTriggerComp::payAndLeave() {
	money->subtractMoney(money->getPrice());
	money->setPrice(0);
	vector<pair<_ecs::_ingredients_id, int>> ing;
	ing = GameManager::get()->getSupermarket()->getUI()->getGameObject(hdr_SM_INVENTORY)->getComponent<BasketMarketComponent>()->getIngredients();
	GameManager::get()->setIngredients(ing);
	GameManager::get()->changeScene(GameManager::get()->getScene(_ecs::sc_RESTAURANT));
	GameManager::get()->getScene(_ecs::sc_RESTAURANT)->reset();
	GameManager::get()->getMoney()->reset();
	GameManager::get()->saveTestFile("Test_", ing);
	restaurantMusic->play(-1);
}

void SuperCashRegisterTriggerComp::sendToClien() {
	Message m;
	m.id = Message::msg_TO_RESTAURANT;
	Game::get()->getCoopHandler()->send(m);
}

void SuperCashRegisterTriggerComp::receive(const Message& message) { 
	if(message.id == Message::msg_TO_RESTAURANT) 
		payAndLeave();
	
}