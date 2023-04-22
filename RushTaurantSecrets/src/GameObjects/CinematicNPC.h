#pragma once
#include "../Structure/GameObject.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/StraightMovement.h"

class CinematicNPC : public GameObject
{
public:

	CinematicNPC(Scene* scene, string sprite, Vector origin, float speed)
		: GameObject(scene, _ecs::grp_CLIENTS) {
		Transform* t = new Transform(this, Vector(origin), Vector(0, 0), 48, 96);
		new CharacterAnimator(this, sprite, 18, 24, 1);
		new StraightMovement(this, speed);
	}
};

