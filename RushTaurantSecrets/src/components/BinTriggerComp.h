#pragma once
#include "../components/TriggerComp.h"
#include "../components/InventoryComp.h"
#include "../components/Image.h"

class BinTriggerComp : public TriggerComp
{
private:
	InventoryComp* inventory;
	Image* highlight;

public:
	BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();	
	virtual void onTriggerExit();

};

