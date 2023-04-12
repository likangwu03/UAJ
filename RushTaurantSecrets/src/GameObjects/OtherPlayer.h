#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CollisionComp.h"
#include "../Components/CharacterAnimator.h"

class OtherPlayer : public GameObject {
public:
	OtherPlayer(Scene* scene) : GameObject(scene) {
		new Transform(this);
		new CollisionComp(this, { 0,48 * sdlutils().getResizeFactor() }, 48 * sdlutils().getResizeFactor(), 48 * sdlutils().getResizeFactor());
		new CharacterAnimator(this, "Player_2", 18, 10, 1);
	}
};