#pragma once
#include "../structure/GameObject.h"
#include "../utilities/Vector.h"
//#include "../components/BinComponent.h"
#include "../components/BinTriggerComp.h"

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
		new Image(this, "BIN_HIGHLIGHT", Vector(pos.getX() + OFFSETX, pos.getY() + OFFSETY), w + OFFSETW, h + OFFSETH); //renderizar el cartel
		new BinTriggerComp(this, Vector(0,0), w, h);
	}
};