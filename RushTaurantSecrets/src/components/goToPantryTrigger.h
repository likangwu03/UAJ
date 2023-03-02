#pragma once
#include "TriggerComp.h"
#include "../structure/Scene.h"
#include "../sdlutils/InputHandler.h"
#include "../structure/SceneManager.h"


class goToPantryTrigger : public TriggerComp {
private:
	InputHandler* ih;
	SceneManager* sceneM;

public:
	goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
		ih = InputHandler::instance();
		sceneM = SceneManager::instance();
	};

	virtual void onTriggerEnter();
};