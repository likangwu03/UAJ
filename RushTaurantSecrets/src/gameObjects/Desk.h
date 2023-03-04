#pragma once
#include "../structure/GameObject.h"
#include "../components/DeskComp.h"

class Desk : public GameObject 
{
public:
	Desk(Scene* scene, Vector pos, float width, float height) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector::zero, width, height);
		new DeskComp(this);
	}
};