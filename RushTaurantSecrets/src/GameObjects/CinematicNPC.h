#pragma once
#include "../Structure/GameObject.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/StraightMovement.h"

class CinematicNPC : public GameObject
{
	const int WIDTH = 48;
	const int HEIGHT = 96;
	const int INIT_FRAME = 18;
	const int END_FRAME = 24;
	const int CURRENT_ANIM = 1;
public:

	CinematicNPC(Scene* scene, string sprite, Vector origin, float speed)
		: GameObject(scene, _ecs::grp_CLIENTS) {
		Transform* t = new Transform(this, Vector(origin), Vector(0, 0), WIDTH, HEIGHT);
		Animator::AnimParams ap;
		ap.initFrame = INIT_FRAME;
		ap.endFrame = END_FRAME;
		ap.currAnim = CURRENT_ANIM;
		new CharacterAnimator(this, sprite, ap);
		new StraightMovement(this, speed);
	}
};

