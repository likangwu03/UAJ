#pragma once
#include "../Structure/GameObject.h"
#include "../Components/ThiefMovement.h"
#include "../Components/ThiefState.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/MurderRender.h"
#include "../Components/ShooRender.h"
#include "../Components/ThiefTrigger.h"

class Thief : public GameObject {
	const int WIDTH = 48;
	const int HEIGHT = 96;
	const int INIT_FRAME = 18;
	const int END_FRAME = 24;
	const int CURRENT_ANIM = 1;
public:
	Thief(Scene* scene, Vector origin, string sprite, float generalSpeed, float escapeSpeed, bool canGetFreezer, int pos) : GameObject(scene, _ecs::grp_THIEFS) {
		SDLUtils* sdl = SDLUtils::instance();
		new Transform(this, origin, Vector(0, 0), WIDTH, HEIGHT);
		Animator::AnimParams ap;
		ap.initFrame = INIT_FRAME;
		ap.endFrame = END_FRAME;
		ap.currAnim = CURRENT_ANIM;
		new CharacterAnimator(this, &(sdl->images().at(sprite)), ap);
		new StraightMovement(this, generalSpeed);
		new ThiefState(this, canGetFreezer);
		new ThiefMovement(this, pos, escapeSpeed);
		new MurderRender(this);
		new ShooRender(this);
		new ThiefTrigger(this, Vector(0, 0), 48, 96);
	}
};