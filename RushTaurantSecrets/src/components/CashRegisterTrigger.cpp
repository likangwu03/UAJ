#include "CashRegisterTrigger.h"
#include "../structure/GameManager.h"
#include "../objects/Reputation.h"
#include "../utils/checkML.h"

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
		int rnd = sdlutils().rand().nextInt(0, 101);
		if (rnd % 2 == 0) sdlutils().soundEffects().at("CASH_REGISTER1").play();
		else sdlutils().soundEffects().at("CASH_REGISTER2").play();

		for (auto it : *list) { //añadir al contador de dinero y de reputación
			_ecs::_dish_id id = it->getComponent<ClientState>()->getOrderedDish();
			int price = _ecs::Dishes[id].price;
			totalPayment += price;
			money->addMoney(price);
			GameManager::instance()->getReputation()->addReputatiton(it->getComponent<ClientState>()->getHappiness() / 100);
		}

		if (GameManager::instance()->getReputation()->getReputation() > rnd) {
			money->addMoney(totalPayment / 10);
#ifdef _DEBUG
			cout << "You got " << totalPayment / 10 << " coins from tips" << endl;
#endif
		}

		cM->collectAndLeave();

	}



}

void CashRegisterTrigger::onTriggerExit() {
	 highlight->setActive(false);
}