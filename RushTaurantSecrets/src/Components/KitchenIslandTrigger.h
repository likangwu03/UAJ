#pragma once

#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "KitchenIslandComp.h"
#include "Transform.h"
class KitchenIslandTrigger :public TriggerComp
{
public:
	KitchenIslandTrigger(GameObject* parent, Vector pos_, float width_, float height_,int i_,int orient_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
private:
	int i;
	KitchenIslandComp* ki;
	Transform* p;
	int orient;
};


