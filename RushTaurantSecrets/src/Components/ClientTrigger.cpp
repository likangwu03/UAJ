#include "ClientTrigger.h"
#include "../Managers/ClientsManager.h"
#include "../Utilities/checkML.h"

void ClientTrigger::isOverlapping() {
	ClientState::States state = clientState->getState();

	if (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B) || !ih->joysticksInitialised() && ih->isKeyDown(SDLK_SPACE)) {
		if (state == ClientState::ENTRANCE) {
			ClientsManager::get()->assignFirstGroup(randomTable());
		}
	}
	else if (state == ClientState::ORDERED) {
		showControl->setActive(true);

		if ((ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A) || !ih->joysticksInitialised() && ih->isKeyDown(SDLK_c)))
		{
			showControl->setActive(false);
			clientState->changeDish();
		}
	}
}

void ClientTrigger::onTriggerExit() {
	showControl->setActive(false);

}
int ClientTrigger::randomTable()
{
	return sdlutils().rand().nextInt(1, _ecs::NUM_TABLES);
}
void ClientTrigger::render() {
	if (showControl->isActive())
		changeIcon->render(build_sdlrect(transform_->getPos().getX() + transform_->getW() / 2 + 5, transform_->getPos().getY() + transform_->getH() / 2 - 35, CHANGE_WIDTH, CHANGE_WIDTH));

}

bool ClientTrigger::inputMando() {

	return ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A);
}
