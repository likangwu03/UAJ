#pragma once
#include "TriggerComp.h"
#include "../components/InventoryComp.h"
#include "../scenes/UIRestaurant.h"
#include "../components/Ingredients.h"
#include "../components/TriggerComp.h"
#include "../components/ClientState.h"
#include "../structure/Paths_def.h"
class ClientTrigger : public TriggerComp
{
	ClientState* clientState;
	InventoryComp* inventory;
public:
	ClientTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_),
		//clientManager(ClientsManager::get()),
		clientState(parent->getComponent<ClientState>()),
		inventory(static_cast<UIRestaurant*>(parent->getScene()->getUI())->getInventory()->getComponent<InventoryComp>()) { };

	virtual void isOverlapping();

	int randomTable();

	bool inputMando();
};

