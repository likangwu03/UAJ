#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/PatryExitTrigger.h"

class PantryExitObj : public GameObject {
private:
public:
	PantryExitObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new PantryExitTrigger(this, Vector(0, 0), w, h);
	}
};
