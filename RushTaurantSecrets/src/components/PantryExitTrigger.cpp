#include "PantryExitTrigger.h"
#include "../structure/SceneManager.h"


PantryExitTrigger::PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	ih = InputHandler::instance();
	sceneM = SceneManager::instance();
};


void PantryExitTrigger::onTriggerEnter() {
	sceneM->setResize(true);
	sceneM->changeScene(static_cast<Pantry*>(parent->getScene())->getRestaurant(), -1);
	parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Transform>()->setPos(Vector(1000, 200));	
}
