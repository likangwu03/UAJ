#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/goToPantryTrigger.h"

class goToPantryObj : public GameObject {
public:
	goToPantryObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new goToPantryTrigger(this, Vector(0, 0), w, h);
	}
};