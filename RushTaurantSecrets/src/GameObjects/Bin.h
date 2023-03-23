#pragma once
#include "../Structure/GameObject.h"
#include "../Utilities/Vector.h"
//#include "../components/BinComponent.h"
#include "../Components/BinTriggerComp.h"

using namespace std;

class Bin : public GameObject
{
private:
	SDLUtils* sdl = SDLUtils::instance();
	const int OFFSETW = 0;
	const int OFFSETH = 4;
	const int OFFSETY = 0;
	const int OFFSETX = 1;
public:
	Bin(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h, 0);
		new Image(this, "BIN_HIGHLIGHT"); //renderizar el highlight		Vector(pos.getX() + OFFSETX, pos.getY() + OFFSETY), w + OFFSETW, h + OFFSETH
		new BinTriggerComp(this, Vector(0,0), w, h);
	}
};