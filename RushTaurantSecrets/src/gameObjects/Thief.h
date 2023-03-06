#pragma once
#include "../structure/GameObject.h"
#include "../components/ThiefMovement.h"
#include "../components/CharacterAnimator.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/MurderRender.h"
#include "../components/ShooRender.h"
#include "../components/ThiefTrigger.h"

class Thief : public GameObject {
public:
	Thief(Scene* scene, Vector origin, string sprite, float generalSpeed, bool canGetFreezer, float escapeSpeed) : GameObject(scene, _ecs::grp_THIEFS) {
		SDLUtils* sdl = SDLUtils::instance();
		new Transform(this, origin, Vector(0, 0), 48, 96);
		new CharacterAnimator(this, &(sdl->images().at(sprite)), 18, 24, 1);
		new StraightMovement(this, generalSpeed);
		new ThiefMovement(this, canGetFreezer, escapeSpeed);
		new MurderRender(this);
		new ShooRender(this);
		new ThiefTrigger(this, Vector(0, 0), 48, 96);
	}
};