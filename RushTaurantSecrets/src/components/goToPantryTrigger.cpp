#include "goToPantryTrigger.h"

void goToPantryTrigger::onTriggerEnter() {
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) {
			//sceneM->changeScene();
			return; 
		}
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) {

		return;
	} 
}
