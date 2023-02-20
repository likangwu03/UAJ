#pragma once
#include "../components/TriggerComp.h"
#include "../components/InventoryComp.h"

class BinTriggerComp : public TriggerComp
{
	InventoryComp* inventory;
public:
	BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();	
};

