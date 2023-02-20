#include "CashRegisterTrigger.h"

void CashRegisterTrigger::isOverlapping() {
	// cout << "hola :)" << endl;
	//if (other_->getComponent<PlayerMovementController>() == nullptr)return; //si no es el jugador, no hace nada
	if (!ih->isKeyDown(SDLK_SPACE) && !ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return; //si no ha interactuado, no hace nada
	
	list<Client*>* list=cM->getPayQueue();
	for (auto it:*list) { //añadir al contador de dinero
		money->addMoney(_ecs::Dishes[it->getComponent<ClientState>()->getOrderedDish()].price);
	}
	cM->collectAndLeave(); //informa al cliente de que ya puede irse
	
}