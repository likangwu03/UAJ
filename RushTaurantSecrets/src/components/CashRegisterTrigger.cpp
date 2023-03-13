#include "CashRegisterTrigger.h"
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
	// informa al cliente de que ya puede irse
	if (cM->collectAndLeave()) {
		list<Client*>* list = cM->getPayQueue();
		for (auto it : *list) { //añadir al contador de dinero y de reputación
			money->addMoney(_ecs::Dishes[it->getComponent<ClientState>()->getOrderedDish()].price);
			Reputation::instance()->addReputatiton(it->getComponent<ClientState>()->getHappiness() / 50);
		}
	}
}

void CashRegisterTrigger::onTriggerExit() {
	 highlight->setActive(false);
}