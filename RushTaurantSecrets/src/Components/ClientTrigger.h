#pragma once
#include "../Structure/TriggerComp.h"
#include "InventoryComp.h"
#include "../Scenes/HUD/UIRestaurant.h"
#include "Ingredients.h"
#include "ClientState.h"
#include "../Definitions/Paths_def.h"

#include "../Structure/GameManager.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include "../Components/ShowControlAuto.h"

class ClientTrigger : public TriggerComp
{
	ClientState* clientState;
	InventoryComp* inventory;
	bool selected;
	ShowControlAuto* showControl;
	Texture* changeIcon;
	const float CHANGE_WIDTH = 40;
public:
	ClientTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_), selected(false),
		//clientManager(ClientsManager::get()),
		clientState(parent->getComponent<ClientState>()),
		inventory(GameManager::get()->getRestaurant()->getUI()->getInventory()->getComponent<InventoryComp>()),
		showControl(new ShowControlAuto(parent, { {ControlsType::key_C,ControlsType::play_Cross,ControlsType::xbox_A,Vector(50, 0),30,30} }, transform_)),
		changeIcon(&sdlutils().images().at("CHANGE_ICON"))
	{ };

	virtual void isOverlapping();

	void onTriggerExit()override;
	int randomTable();

	void render()override;
	bool inputMando();

	bool isSelected() { return selected; }
};

