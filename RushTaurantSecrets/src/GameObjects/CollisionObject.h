#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CollisionComp.h"
#include "../Utilities/SDLUtils.h"

class Scene;
class CollisionObject :public GameObject {
public:
	CollisionObject(Scene* scene,Vector pos,float w,float h) :GameObject(scene, _ecs::grp_COLLISIONS) {
		new Transform(this, pos, { 0,0 }, w, h);
	}
};