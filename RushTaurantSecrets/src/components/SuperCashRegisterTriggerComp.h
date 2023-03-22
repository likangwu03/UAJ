#pragma once
#include "../components/TriggerComp.h"
#include "../components/InventoryComp.h"
#include "../components/Image.h"

class SuperCashRegisterTriggerComp : public TriggerComp
{
private:
	Image* highlight;

public:
	SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();
	virtual void onTriggerExit();
};

