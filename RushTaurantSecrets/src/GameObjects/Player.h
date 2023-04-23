#pragma once
#include "../Structure/GameObject.h"
#include "../Utilities/SDLUtils.h"
#include "../Components/CharacterAnimator.h"
#include "../Utilities/Texture.h"
#include "../Components/Ingredients.h"
#include "../Components/Transform.h"
#include "../Components/CollisionComp.h"
#include "../Components/PlayerMovementController.h"
class Player :public GameObject
{
private:
	int player;

	const int INIT_POS_X = 500;
	const int INIT_POS_Y = 200;
	const int WIDTH = 48;
	const int HEIGHT = 96;
	const int INIT_FRAME = 18;
	const int END_FRAME = 18;
	const int CURRENT_ANIM = 1;
public:
	Player(Scene * scene, int _player) :GameObject(scene, _ecs::grp_PLAYER, _ecs::hdr_PLAYER), player(_player) {
		new Transform(this, Vector(INIT_POS_X, INIT_POS_Y), Vector(0, 0), WIDTH, HEIGHT);
		new PlayerMovementController(this, player);
		new CollisionComp(this, { 0, WIDTH * sdlutils().getResizeFactor() }, WIDTH * sdlutils().getResizeFactor(), WIDTH * sdlutils().getResizeFactor());
		Animator::AnimParams ap;
		ap.initFrame = INIT_FRAME;
		ap.endFrame = END_FRAME;
		ap.currAnim = CURRENT_ANIM;
		new CharacterAnimator(this, "Player_1", ap);
		new Ingredients(this);
	}
};

