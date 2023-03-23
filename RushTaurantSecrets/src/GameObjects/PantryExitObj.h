#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/PantryExitTrigger.h"

class PantryExitObj : public GameObject {
private:
public:
	PantryExitObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new PantryExitTrigger(this, Vector(0, 0), w, h);
	}
};
