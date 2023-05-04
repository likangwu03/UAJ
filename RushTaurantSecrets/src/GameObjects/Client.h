#pragma once
#include "../Structure/GameObject.h"
#include "../Components/CharacterAnimator.h"
#include "../Components/StraightMovement.h"
#include "../Components/ClientState.h"
#include "../Definitions/Food_def.h"
#include "../Components/ClientMovement.h"
#include "../Components/ClientTrigger.h"
#include "../Components/UIAnimator.h"
#include "../Components/ClientStateRender.h"
#include "../Components/HeartRender.h"

class Client : public GameObject {
	const int THINKING_WIDTH = 48;
	const int THINKING_HEIGHT = 48;
	const int THINKING_OFFSETY = -48;
	const int CHAR_INIT_FRAME = 18;
	const int CHAR_END_FRAME = 24;
	const int CHAR_CURRENT_ANIM = 1;
	const int CHAR_WIDTH = 48;
	const int CHAR_HEIGHT = 96;

	const int UI_INIT_FRAME = 0;
	const int UI_END_FRAME = 8;
	const int UI_CURR_ANIM = 0;
	const int UI_FRAME_RATE = 80;

	const int HEART_SIZE = 24;
	const int HEART_OFFSET_Y = 20;

public:

	Client(Scene* scene, string sprite, Vector origin, vector<_ecs::DishInfo>* menu, int posEntrance, float speed, int posGroup) 
		: GameObject(scene, _ecs::grp_CLIENTS) {
		Transform* t = new Transform(this, Vector(origin), Vector(0, 0), CHAR_WIDTH, CHAR_HEIGHT);

		Animator::AnimParams aP;
		aP.initFrame = CHAR_INIT_FRAME;
		aP.endFrame = CHAR_END_FRAME;
		aP.currAnim = CHAR_CURRENT_ANIM;
		new CharacterAnimator(this, sprite, aP);

		aP.initFrame = UI_INIT_FRAME;
		aP.endFrame = UI_END_FRAME;
		aP.currAnim = UI_CURR_ANIM;
		aP.frameRate = UI_FRAME_RATE;
		aP.width = THINKING_WIDTH;
		aP.height = THINKING_HEIGHT;
		new UIAnimator(this, "CLIENT_THINKING_ICON_ANIM", aP, Vector(origin.getX(), origin.getY() + THINKING_OFFSETY));

		new StraightMovement(this, speed);
		ClientMovement* mov = new ClientMovement(this, posEntrance, posGroup);
		new ClientStateRender(this);
		new ClientState(this, menu);
		// se guarda en clientMovement la referencia a ClientState
		mov->initState();
		new ClientTrigger(this, Vector(0, 0), CHAR_WIDTH, CHAR_HEIGHT);
		new HeartRender(this, &sdlutils().images().at("HEARTS"), HEART_SIZE, HEART_SIZE, HEART_OFFSET_Y);
	}
};