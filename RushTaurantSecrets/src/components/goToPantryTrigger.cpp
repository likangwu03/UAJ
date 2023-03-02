#include "goToPantryTrigger.h"
#include "../structure/SceneManager.h"
goToPantryTrigger::goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	ih = InputHandler::instance();
	sceneM = SceneManager::instance();
};
void goToPantryTrigger::isOverlapping() {
	//hacerlo en un solo if como dijo el profesor
	if (ih->joysticksInitialised()) {
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) {
			sceneM->setResize(false);
			sceneM->changeScene(static_cast<Restaurant*>(parent->getScene())->getPantry(), -1);
			return; 
		}
	}
	else if (ih->isKeyDown(SDLK_SPACE)) {
		sceneM->setResize(false);
		sceneM->changeScene(static_cast<Restaurant*>(parent->getScene())->getPantry(), -1);
		return;
	} 
}
