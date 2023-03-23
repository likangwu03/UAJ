#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/goToPantryTrigger.h"

class goToPantryObj : public GameObject {
public:
	goToPantryObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new goToPantryTrigger(this, Vector(0, 0), w, h);
	}
};