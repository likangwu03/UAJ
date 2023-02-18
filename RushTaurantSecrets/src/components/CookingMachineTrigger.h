#pragma once
#include "../components/CookingMachineComp.h"
#include "../components/InventoryComp.h"
#include "../scenes/UIRestaurant.h"
#include "../components/Ingredients.h"
#include "../components/TriggerComp.h"

/*gestiona la cocina cuando se colisiona con player*/
class CookingMachineTrigger :public TriggerComp
{
public:
	CookingMachineTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_,width_,height_),
		cook(parent->getComponent<CookingMachineComp>()),
		inventory(static_cast<UIRestaurant*>(parent->getScene()->getUI())->getInventory()->getComponent<InventoryComp>()) {};
	
	virtual void isOverlapping();
private:
	SDLUtils* sdl;
	InventoryComp* inventory;
	CookingMachineComp* cook;
};

