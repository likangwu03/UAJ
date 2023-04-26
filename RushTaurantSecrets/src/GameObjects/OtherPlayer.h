#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CollisionComp.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/OtherPlayerComp.h"

class OtherPlayer : public GameObject {
	const int WIDTH = 48;
	const int HEIGHT = 96;
	const int INIT_FRAME = 18;
	const int END_FRAME = 10;
	const int CURRENT_ANIM = 1;
public:
	OtherPlayer(Scene* scene, uint8_t sceneID) : GameObject(scene, _ecs::grp_GENERAL, _ecs::hdr_OTHERPLAYER) {
		new Transform(this, Vector(-100, -100), Vector::zero, WIDTH, HEIGHT);
		new CollisionComp(this, { 0,WIDTH * sdlutils().getResizeFactor() }, WIDTH * sdlutils().getResizeFactor(), WIDTH * sdlutils().getResizeFactor());
		Animator::AnimParams ap;
		ap.initFrame = INIT_FRAME;
		ap.endFrame = END_FRAME;
		ap.currAnim = CURRENT_ANIM;
		new CharacterAnimator(this, "Player_2", ap);
		new OtherPlayerComp(this, sceneID);
		scene->pushRenderList(Middle, this);
	}
};