#pragma once
#include "../Structure/TriggerComp.h"

class SceneManager;
class goToPantryTrigger : public TriggerComp {

public:
	goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
};