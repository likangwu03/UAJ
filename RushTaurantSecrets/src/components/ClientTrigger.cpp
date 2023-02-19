#include "ClientTrigger.h"
#include "../objects/ClientsManager.h"

void ClientTrigger::isOverlapping()
{
	if (ih->isKeyDown(SDLK_SPACE)) {
		ClientState::States state = clientState->getState();
		switch (state)
		{
		case ClientState::ENTRANCE:
			ClientsManager::get()->assignFirstClient(randomTable());
			break;
		case ClientState::TAKEMYORDER:
			std::cout << "Aaaaaa" << std::endl;
			clientState->takeOrder();
			break;
		case ClientState::ORDERED:
			//temporal, no comprueba si esta el plato que quiere, solo comprueba que el jugador tenga platos
			if (inventory->freeSpace() != 0) {
				//inventory->freeDish();
				clientState->getServed();
				std::cout << "nam nam" << std::endl;
			}
			break;
		default:
			break;
		}
	}
}

int ClientTrigger::randomTable()
{
	int table = SDLUtils::instance()->rand().nextInt(1, 5);
	if (table == 3) {
		table = 4;
	}
	return table;
}
