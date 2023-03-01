#pragma once
#include "../structure/GameObject.h"

#include "../components/Ingredients.h"
#include "../components/Transform.h"

class IngredientBubble :public GameObject
{
private:
public:
	IngredientBubble(Scene* scene, GameObject* player) : GameObject(scene, _ecs::grp_HUD) {
		new Ingredients(this, player->getComponent<Transform>() );
	}
};

