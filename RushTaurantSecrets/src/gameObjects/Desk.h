#pragma once
#include "../structure/GameObject.h"

class Desk : public GameObject {
public:
	Desk(Scene* scene) : GameObject(scene, _ecs::grp_INTERACTABLE) { }
};