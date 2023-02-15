#pragma once
#include "../structure/GameObject.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Animator.h"
#include "../sdlutils/Texture.h"

class Player :public GameObject
{
public:
	Player(Scene* scene) :GameObject(scene, _ecs::hdr_PLAYER, _ecs::grp_PLAYER) {
		//auto& sdl = *SDLUtils::instance();
		//new CookingMachineComp(this);
		//new Animator(this, &(sdl.images().at("Player_1")), 6, 2);
	};
};

