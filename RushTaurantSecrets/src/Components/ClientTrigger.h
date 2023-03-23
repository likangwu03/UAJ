#pragma once
#include "../Structure/TriggerComp.h"
#include "InventoryComp.h"
#include "../Scenes/UIRestaurant.h"
#include "Ingredients.h"
#include "ClientState.h"
#include "../Definitions/Paths_def.h"

#include "../Structure/GameManager.h"
#include "../Scenes/Restaurant.h"

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
		inventory(GameManager::get()->getRestaurant()->getUI()->getInventory()->getComponent<InventoryComp>()) { };

	virtual void isOverlapping();

	int randomTable();

	bool inputMando();

	bool isSelected() { return selected; }
};

