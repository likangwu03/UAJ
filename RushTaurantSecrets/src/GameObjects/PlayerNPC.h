#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/StraightMovement.h"
#include "../Components/CharacterAnimator.h"

class PlayerNPC : public GameObject {
private:


public:
	PlayerNPC(Scene* scene, Vector initialPos, float speed) : GameObject(scene, _ecs::grp_PLAYER) {
		new Transform(this, initialPos, Vector(0, 0), 48, 96);
		new StraightMovement(this, speed);
		Animator::AnimParams ap;
		ap.initFrame = 18;
		ap.endFrame = 18;
		ap.currAnim = 1;
		ap.width = 48;
		ap.height = 96;
		new CharacterAnimator(this, "Player_1", ap);
	}
};