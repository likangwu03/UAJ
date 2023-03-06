#include "../components/PantryExitTrigger.h"
#include "../structure/SceneManager.h"


PantryExitTrigger::PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	ih = InputHandler::instance();
	sceneM = SceneManager::instance();
}


void PantryExitTrigger::isOverlapping() {
	sceneM->setResize(false);
	//sceneM->changeScene(static_cast<Restaurant*>(parent->getScene())->getRestaurant(), -1);
}
