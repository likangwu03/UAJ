#pragma once
#include "../components/TriggerComp.h"
#include "../components/Transform.h"
#include "../components/Ingredients.h"
#include "../gameObjects/Player.h"


class onKitchenExit : public TriggerComp
{
private:
	SDLUtils* sdl;
	Ingredients* ing;
	Player* player;

public:
	onKitchenExit(GameObject* parent, Vector pos_, float width_, float height_) : 
		TriggerComp(parent, pos_, width_, height_), ing(player->getComponent<Ingredients>()) {}

	virtual void onTriggerExit();
};

