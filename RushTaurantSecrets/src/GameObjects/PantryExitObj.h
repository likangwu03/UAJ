#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/PantryExitTrigger.h"
#include "../Components/Image.h"

class PantryExitObj : public GameObject {
private:
public:
	PantryExitObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new Image(this, "DOOR_HIGHLIGHT", Vector(0,7));
		new PantryExitTrigger(this, Vector(0, 0), w, h);
		scene->pushRenderList(Top, this);
	}
};
