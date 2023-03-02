#include "goToPantryTrigger.h"
#include "../scenes/Restaurant.h"

void goToPantryTrigger::isOverlapping() {
	//hacerlo en un solo if como dijo el profesor
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) {
			sceneM->setResize(false);
			//sceneM->changeScene(pantry, -1);
			return; 
		}
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) {
		sceneM->setResize(false);
		//sceneM->changeScene(pantry, -1);		
		return;
	} 
}
