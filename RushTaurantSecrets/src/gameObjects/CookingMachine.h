#pragma once
#include "../structure/GameObject.h"
#include "../components/CookingMachineComp.h"
using namespace std;

class CookingMachine:public GameObject
{
public:

	CookingMachine(Scene* scene) :GameObject(scene, _ecs::grp_INTERACTABLE, _ecs::hdr_DISHCOMB) {
		new CookingMachineComp(this);
	};
};

