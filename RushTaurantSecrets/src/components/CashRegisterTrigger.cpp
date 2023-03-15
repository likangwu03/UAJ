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

	list<Client*>* list = cM->getPayQueue();
	int totalPayment = 0;
	for (auto it : *list) { //añadir al contador de dinero y de reputación
		totalPayment += _ecs::Dishes[it->getComponent<ClientState>()->getOrderedDish()].price;
		money->addMoney(_ecs::Dishes[it->getComponent<ClientState>()->getOrderedDish()].price);
		GameManager::instance()->getReputation()->addReputatiton(it->getComponent<ClientState>()->getHappiness() / 100);
	}
	int rnd = sdlutils().rand().nextInt(0, 101);
	if(GameManager::instance()->getReputation()->getReputation() > rnd)
		money->addMoney(totalPayment / 10);

}

void CashRegisterTrigger::onTriggerExit() {
	 highlight->setActive(false);
}