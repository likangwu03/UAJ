﻿#include "CashRegisterTrigger.h"
#include "../Structure/GameManager.h"
#include "../Managers/Reputation.h"
#include "../Utilities/SoundEffect.h"
#include "../Utilities/checkML.h"

CashRegisterTrigger::CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), money(GameManager::get()->getMoney()),
	cM(ClientsManager::get()), highlight(parent->getComponent<Image>()), 
	addSound(&sdlutils().soundEffects().at("GAIN_REPUTATION")),
	tipSound(&sdlutils().soundEffects().at("TIP")),
	cashSound1(&sdlutils().soundEffects().at("CASH_REGISTER1")),
	cashSound2(&(sdlutils().soundEffects().at("CASH_REGISTER2"))) {
	cashSound1->setVolume(10);
	cashSound2->setVolume(7);
	highlight->setActive(false);
	list = cM->getPayQueue();
	streak = GameManager::get()->getRestaurant()->getUI()->getGameObject(_ecs::hdr_STREAK)->getComponent<Streak>();
}

void CashRegisterTrigger::isOverlapping() {
	if (other_->getComponent<Transform>()->getOrientation() != south) {
		highlight->setActive(false); return;
	};
	highlight->setActive(true);
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada

	if (cM->canCollect()) {
		int totalPayment = 0;

		// SONIDO CAJA REGISTRADORA
		if (sdlutils().rand().nextInt(0, 2) == 0) cashSound1->play(0);
		else cashSound2->play(0);

		// AÑADIR DINERO Y REPUTACIÓN
		for (auto it : *list) {
			_ecs::_dish_id id = it->getComponent<ClientState>()->getOrderedDish();
			int price = _ecs::Dishes[id].price;
			totalPayment += price;
			money->addMoney(price);
			GameManager::get()->getReputation()->addReputatiton(it->getComponent<ClientState>()->getHappiness() / 100);
			addSound->play(0);
		}

		// PROPINAS
		if (GameManager::get()->getReputation()->getReputation() > sdlutils().rand().nextInt(0, 101)) {
			money->addMoney(totalPayment / 10);
			tipSound->play(0);
#ifdef _DEBUG
			cout << "You got " << totalPayment / 10 << " coins from tips" << endl;
#endif
		}

		// RACHA
		money->addMoney(streak->getMoneyStreak() * list->size());
		streak->setStreak(list->size());

		// CLIENTES ABANDONAN CAJA
		cM->collectAndLeave();

	}
}

void CashRegisterTrigger::onTriggerExit() {
	 highlight->setActive(false);
}