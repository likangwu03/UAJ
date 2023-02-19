#pragma once
#include "../components/TriggerComp.h"
#include "../components/InventoryComp.h"
//#include "../scenes/UIRestaurant.h"

class BinTriggerComp : public TriggerComp
{
public:
	BinTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_)
		//inventory(static_cast<UIRestaurant*>(parent->getScene()->getUI())->getInventory()->getComponent<InventoryComp>()) 
	{};

private:
	InventoryComp* inventory;
	
};

