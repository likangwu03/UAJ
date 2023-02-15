#pragma once
#include "../structure/GameObject.h"
class Player :public GameObject
{
public:
	Player(Scene* scene) :GameObject(scene, _ecs::hdr_PLAYER, _ecs::grp_PLAYER) {
		//new CookingMachineComp(this);
		
	};
};

