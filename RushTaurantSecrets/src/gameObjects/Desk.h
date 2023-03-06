#pragma once
#include "../structure/GameObject.h"
#include "../components/DeskComp.h"

class Desk : public GameObject 
{
public:
	Desk(Scene* scene, Vector pos, float width, float height, int id) : GameObject(scene, _ecs::grp_DESK) {
		new Transform(this, pos, Vector::zero, width, height);
		new DeskComp(this, width, height, id);
	}
};