#pragma once
#include "TriggerComp.h"

class SceneManager;
class PantryExitTrigger : public TriggerComp {
private:
	SceneManager* sceneM;
	InputHandler* ih;

public:
	PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
};
