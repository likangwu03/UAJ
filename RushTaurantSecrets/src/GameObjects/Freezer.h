#pragma once
#include "../Structure/GameObject.h"
#include "../Components/CookingMachineComp.h"
#include "../Components/CookingMachineTrigger.h"
#include "../Components/UIAnimator.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/FreezerComp.h"
using namespace std;
class Freezer :public GameObject
{
private:

public:
	Freezer(Scene* scene, Vector pos, float w, float h) :GameObject(scene,grp_GENERAL, hdr_FREEZER) {
		new Transform(this, pos, Vector(0, 0), w, h, 0, true); 
		new Image(this, "FREEZER_OPEN");
		new FreezerComp(this);
		scene->pushRenderList(Middle, this);
	};
};