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
		new Transform(this, pos, Vector(0, 0), 50, 50, 0);
		new BinComponent(this, pos);
		// icono temporal, cambiar cuando se haya implementado la animación de la papelera
		new Image(this, &((*sdl).images().at("MONEY_ICON")));
	}
};