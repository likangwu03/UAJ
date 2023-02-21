#pragma once
#include "../structure/GameObject.h"
#include "../components/ThiefMovement.h"
#include "../components/CharacterAnimator.h"
#include "../components/Transform.h"
#include "../components/Image.h"

class Thief : public GameObject {
public:
	Thief(Scene* scene, bool canGetFreezer, Vector origin, float generalSpeed, float escapeSpeed) : GameObject(scene, _ecs::grp_THIEFS) {
		SDLUtils* sdl = SDLUtils::instance();
		new Transform(this, Vector(origin.getX() * sdl->width() / 40, origin.getY() * sdl->height() / 23), Vector(0, 0), 48, 96);
		new CharacterAnimator(this, &(SDLUtils::instance()->images().at("Customer_2")), 0, 6, 1);
		new StraightMovement(this, generalSpeed);
		new ThiefMovement(this, canGetFreezer, escapeSpeed);
	}
};