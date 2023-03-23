#pragma once
#include "../Structure/GameObject.h"
#include "../Components/ThiefMovement.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/MurderRender.h"
#include "../Components/ShooRender.h"
#include "../Components/ThiefTrigger.h"

class Thief : public GameObject {
public:
	Thief(Scene* scene, Vector origin, string sprite, float generalSpeed, float escapeSpeed, Objective objective, int pos) : GameObject(scene, _ecs::grp_THIEFS) {
		SDLUtils* sdl = SDLUtils::instance();
		new Transform(this, origin, Vector(0, 0), 48, 96);
		new CharacterAnimator(this, &(sdl->images().at(sprite)), 18, 24, 1);
		new StraightMovement(this, generalSpeed);
		new ThiefMovement(this, objective, pos, escapeSpeed);
		new MurderRender(this);
		new ShooRender(this);
		new ThiefTrigger(this, Vector(0, 0), 48, 96);
	}
};