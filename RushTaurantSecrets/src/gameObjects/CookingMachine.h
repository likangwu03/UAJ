#pragma once
#include "../structure/GameObject.h"
#include "../components/CookingMachineComp.h"
using namespace std;

class CookingMachine:public GameObject
{
public:

	CookingMachine(Scene* scene) :GameObject(scene, _ecs::hdr_DISHCOMB, _ecs::grp_INTERACTABLE) {
		new CookingMachineComp(this);
	};
};

