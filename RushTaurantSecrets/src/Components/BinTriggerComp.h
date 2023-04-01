#pragma once
#include "../Structure/TriggerComp.h"
#include "InventoryComp.h"
#include "Image.h"

class BinTriggerComp : public TriggerComp
{
private:
	InventoryComp* inventory;
	Image* highlight;
	SoundEffect* throwDish;
public:
	BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();	
	virtual void onTriggerExit();

};

