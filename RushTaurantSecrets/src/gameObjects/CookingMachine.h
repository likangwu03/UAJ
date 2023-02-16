#pragma once
#include "../structure/GameObject.h"
#include "../components/CookingMachineComp.h"
#include "../components/Transform.h"
using namespace std;

class CookingMachine:public GameObject
{
public:

	CookingMachine(Scene* scene,Vector pos) :GameObject(scene, _ecs::grp_INTERACTABLE, _ecs::hdr_DISHCOMB) {
		new CookingMachineComp(this,pos);
		//new Transform(this, pos); //para saber en qu¨¦ posici¨®n renderizar el bocadillo 
	};
};

