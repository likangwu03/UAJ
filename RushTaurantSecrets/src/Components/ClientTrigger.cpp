#include "ClientTrigger.h"
#include "../Managers/ClientsManager.h"

#include "../Utilities/checkML.h"

void ClientTrigger::isOverlapping()
{
		ClientState::States state = clientState->getState();
		if (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B) || !ih->joysticksInitialised() &&ih->isKeyDown(SDLK_SPACE)  ) {
			switch (state)
			{
			case ClientState::ENTRANCE:
				ClientsManager::get()->assignFirstGroup(randomTable());
				break;
			case ClientState::TAKEMYORDER:
				clientState->takeOrder();
				break;
			case ClientState::ORDERED:
				//temporal, no comprueba si esta el plato que quiere, solo comprueba que el jugador tenga platos
				if (inventory->serveDish(clientState->getOrderedDish())) {
					clientState->getServed();
				}
				break;
			default:
				break;
			}
		}
		else if (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A) || !ih->joysticksInitialised() && ih->isKeyDown(SDLK_c) )
			clientState->changeDish();
}

int ClientTrigger::randomTable()
{
	return sdlutils().rand().nextInt(1, _ecs::NUM_TABLES);
}

bool ClientTrigger::inputMando() {
	//if (ih->joysticksInitialised()) {
	//	if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
	//		return true;
	//	}
	//}
	//else
	//	return false;

	return ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A);
}
