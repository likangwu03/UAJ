#pragma once
#include "../Structure/GameObject.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/Vector.h"
#include "../Components/SuperCashRegisterTriggerComp.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"

class SuperCashRegister : public GameObject
{
private:
	SDLUtils* sdl = SDLUtils::instance();
	const int OFFSETW = 0;
	const int OFFSETH = 4;
	const int OFFSETY = 0;
	const int OFFSETX = 1;
public:
	SuperCashRegister(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h, 0);
		new Image(this, "SUPER_CASHREGISTER"); //renderizar el cartel  // Vector(pos.getX() + OFFSETX, pos.getY() + OFFSETY), w + OFFSETW, h + OFFSETH
		new SuperCashRegisterTriggerComp(this, Vector(0, 0), w, h);
	}
};

