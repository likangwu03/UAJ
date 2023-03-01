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
public:
	Bin(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE, _ecs::hdr_BIN) {
		new Transform(this, pos, Vector(0, 0), w, h, 0);
		new BinTriggerComp(this, Vector(0,0), w, h);
	}
};