#pragma once
#include "TriggerComp.h"

class SceneManager;
class goToPantryTrigger : public TriggerComp {
private:
	SceneManager* sceneM;
public:
	goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
};