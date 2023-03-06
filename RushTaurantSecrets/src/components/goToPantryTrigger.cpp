#include "goToPantryTrigger.h"
#include "../structure/SceneManager.h"
goToPantryTrigger::goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	ih = InputHandler::instance();
	sceneM = SceneManager::instance();
};
void goToPantryTrigger::onTriggerEnter() {
	sceneM->setResize(false);
	sceneM->changeScene(static_cast<Restaurant*>(parent->getScene())->getPantry(), -1);
}
