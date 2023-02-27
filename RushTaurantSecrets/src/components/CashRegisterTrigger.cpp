#include "CashRegisterTrigger.h"

#include "../objects/Reputation.h"

#include "../utils/checkML.h"

void CashRegisterTrigger::isOverlapping() {
	// cout << "hola :)" << endl;
	//if (other_->getComponent<PlayerMovementController>() == nullptr)return; //si no es el jugador, no hace nada
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada
	if (other_->getComponent<Transform>()->getOrientation() != south) return;
	list<Client*>* list=cM->getPayQueue();
	for (auto it:*list) { //añadir al contador de dinero y de reputación
		money->addMoney(_ecs::Dishes[it->getComponent<ClientState>()->getOrderedDish()].price);
		Reputation::instance()->addReputatiton(it->getComponent<ClientState>()->getHappiness() / 10);
	}
	cM->collectAndLeave(); //informa al cliente de que ya puede irse
	
}