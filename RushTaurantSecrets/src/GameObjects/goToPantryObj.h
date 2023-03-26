#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/goToPantryTrigger.h"
#include "../Components/Image.h"

class GoToPantryObj : public GameObject {
public:
	GoToPantryObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new Image(this, "DOOR_HIGHLIGHT", Vector(0, -3));
		new GoToPantryTrigger(this, Vector(0, 0), w, h);
	}
};