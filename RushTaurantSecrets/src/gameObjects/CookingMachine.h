#pragma once
#include "../structure/GameObject.h"
#include "../components/CookingMachineComp.h"
#include "../components/CookingMachineTrigger.h"
#include "../components/Animator.h"
#include "../components/Transform.h"

using namespace std;
class CookingMachine :public GameObject
{
	const int OFFSETY = 48;
	const int THINKING_WIDTH = 48;
	const int THINKING_HEIGHT = 48;
	const int THINKING_OFFSETY = -48;
public:
	CookingMachine(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h,0,true); //para saber en qu¨¦ posici¨®n renderizar el bocadillo 
		new Animator(this, "THINKING_ICON_ANIM", 0, 8, 0,80,THINKING_WIDTH,THINKING_HEIGHT,Vector(pos.getX(),pos.getY()+ THINKING_OFFSETY));
		new CookingMachineComp(this);
		new CookingMachineTrigger(this, Vector(0,OFFSETY), w, h);
	};
};

