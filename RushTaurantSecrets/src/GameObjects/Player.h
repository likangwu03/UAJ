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
public:
	Player(Scene * scene, int _player) :GameObject(scene, _ecs::grp_PLAYER, _ecs::hdr_PLAYER), player(_player) {
		new Transform(this, Vector(500, 200), Vector(0, 0), 48, 96, 0);
		new PlayerMovementController(this, player);
		new CollisionComp(this, { 0,48 * sdlutils().getResizeFactor() }, 48 * sdlutils().getResizeFactor(), 48 * sdlutils().getResizeFactor());
		new CharacterAnimator(this, "Player_1", 18, 10, 1);
		new Ingredients(this);
	}
};

