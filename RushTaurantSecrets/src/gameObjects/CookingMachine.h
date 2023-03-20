#pragma once
#include "../structure/GameObject.h"
#include "../components/CookingMachineComp.h"
#include "../components/CookingMachineTrigger.h"
#include "../components/UIAnimator.h"
#include "../components/Transform.h"
#include "../components/Image.h"
using namespace std;
class CookingMachine :public GameObject
{
private:
	const int OFFSET_Y = 48;
	const int THINKING_WIDTH = 48;
	const int THINKING_HEIGHT = 48;
	const int THINKING_OFFSETY = -48;
	const int OFFSETW = 6;
	const int OFFSETH = -2;
	const int OFFSETY = 0;
	const int OFFSETX = -7;
public:
	CookingMachine(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h,0,true); //para saber en qu¨¦ posici¨®n renderizar el bocadillo 
		new UIAnimator(this, "KITCHEN_PROCESSING_ICON_ANIM", 0, 8, 0, 0, THINKING_WIDTH, THINKING_HEIGHT, Vector(pos.getX(), pos.getY()+ THINKING_OFFSETY));
		new CookingMachineComp(this);
		new Image(this, "COOK_HIGHLIGHT"); //renderizar el cartel  Vector(pos.getX() + OFFSETX, pos.getY() + OFFSETY), w + OFFSETW, h + OFFSETH
		new CookingMachineTrigger(this, Vector(0,OFFSET_Y), w, h);
	};
};

