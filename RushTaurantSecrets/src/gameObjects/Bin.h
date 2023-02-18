#pragma once
#include "../structure/GameObject.h"
#include "../utilities/Vector.h"
#include "../components/BinComponent.h"

using namespace std;

class Bin : public GameObject
{
private:
	SDLUtils* sdl = SDLUtils::instance();
public:
	Bin(Scene* scene, Vector pos) :GameObject(scene, _ecs::grp_INTERACTABLE, _ecs::hdr_BIN) {
		new Transform(this, pos, Vector(0, 0), 37, 46, 0);
		new BinComponent(this, pos);
		new Image(this, &((*sdl).images().at("BIN")));
	}
};