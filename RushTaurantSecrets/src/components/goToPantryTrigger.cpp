#include "goToPantryTrigger.h"
#include "../structure/SceneManager.h"
#include "../utils/checkML.h"

goToPantryTrigger::goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	ih = InputHandler::instance();
	sceneM = SceneManager::instance();
};
void goToPantryTrigger::onTriggerEnter() {
	sceneM->setResize(false);
	sceneM->changeScene(static_cast<Restaurant*>(parent->getScene())->getPantry(), -1);
	parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setPos(Vector(950,700));
}
