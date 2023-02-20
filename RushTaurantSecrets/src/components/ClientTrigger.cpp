#include "ClientTrigger.h"
#include "../objects/ClientsManager.h"

void ClientTrigger::isOverlapping()
{
	if (ih->isKeyDown(SDLK_SPACE) || inputMando()) {
		ClientState::States state = clientState->getState();
		switch (state)
		{
		case ClientState::ENTRANCE:
			ClientsManager::get()->assignFirstClient(randomTable());
			break;
		case ClientState::TAKEMYORDER:
			clientState->takeOrder();
			break;
		case ClientState::ORDERED:
			//temporal, no comprueba si esta el plato que quiere, solo comprueba que el jugador tenga platos
			if (inventory->freeSpace() != 0) {
				inventory->freeDish();
				clientState->getServed();
			}
			break;
		default:
			break;
		}
	}
}

int ClientTrigger::randomTable()
{
	return SDLUtils::instance()->rand().nextInt(1, _ecs::NUM_TABLES + 1);
}

bool ClientTrigger::inputMando() {
	if (ih->joysticksInitialised()) {
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
			return true;
		}
	}
	else
		return false;
}
