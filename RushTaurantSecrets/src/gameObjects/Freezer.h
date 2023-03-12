#pragma once
#include "../structure/GameObject.h"
#include "../components/CookingMachineComp.h"
#include "../components/CookingMachineTrigger.h"
#include "../components/UIAnimator.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/FreezerComp.h"
using namespace std;
class Freezer :public GameObject
{
private:

public:
	Freezer(Scene* scene, Vector pos, float w, float h) :GameObject(scene) {
		new Transform(this, pos, Vector(0, 0), w, h, 0, true); 
		new Image(this, "FREEZER_OPEN");
		new FreezerComp(this);
	};
};

