#pragma once
#include "TriggerComp.h"

class SceneManager;
class PantryExitTrigger : public TriggerComp {
private:
	SceneManager* sceneM;
public:
	PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
};
