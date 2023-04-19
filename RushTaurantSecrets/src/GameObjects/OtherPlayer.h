#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CollisionComp.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/OtherPlayerComp.h"

class OtherPlayer : public GameObject {
public:
	OtherPlayer(Scene* scene) : GameObject(scene, _ecs::grp_GENERAL, _ecs::hdr_OTHERPLAYER) {
		new Transform(this, Vector::zero, Vector::zero, 48, 96);
		new CollisionComp(this, { 0,48 * sdlutils().getResizeFactor() }, 48 * sdlutils().getResizeFactor(), 48 * sdlutils().getResizeFactor());
		new CharacterAnimator(this, "Player_2", 18, 10, 1);
		new OtherPlayerComp(this);
		scene->pushRenderList(Middle, this);
	}
};