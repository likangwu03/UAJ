#pragma once
#include "../Structure/TriggerComp.h"
#include "InventoryComp.h"
#include "Image.h"

class SuperCashRegisterTriggerComp : public TriggerComp
{
private:
	Image* highlight;

public:
	SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();
	virtual void onTriggerExit();
};

