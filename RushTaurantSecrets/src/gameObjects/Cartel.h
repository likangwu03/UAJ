#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/CartelTrigger.h"
#include "../components/Image.h"
#include "../structure/Food_def.h"
using namespace std;
/*Cartel del supermercado*/
class Cartel :public GameObject
{
private:
	const int HIGH_OFFSETX = -1;
	const int HIGH_OFFSETY = 1;
	const int HIGH_OFFSETW = 3;
	const int HIGH_OFFSETH = -1;
public:
	Cartel(Scene* scene, _ecs::_ingredients_id ingId, Vector pos, float w, float h, Vector triP, float triW, float triH) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, Vector(pos.getX() + HIGH_OFFSETX, pos.getY() + HIGH_OFFSETY), Vector(0, 0), w + HIGH_OFFSETW , h + HIGH_OFFSETH, 0, true); //renderizar el cartel
		new Image(this, "CARTEL_HIGHLIGHT"); //renderizar el cartel
		new CartelTrigger(this, ingId, triP - pos, w, h); //pos relativa
	};
};

