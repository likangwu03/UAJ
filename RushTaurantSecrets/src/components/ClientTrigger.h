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
	bool selected;
public:
	ClientTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_), selected(false),
		//clientManager(ClientsManager::get()),
		clientState(parent->getComponent<ClientState>()),
		inventory(static_cast<UIRestaurant*>(parent->getScene()->getConnectedScene())->getInventory()->getComponent<InventoryComp>()) { };

	virtual void isOverlapping();

	int randomTable();

	bool inputMando();

	bool isSelected() { return selected; }
};

