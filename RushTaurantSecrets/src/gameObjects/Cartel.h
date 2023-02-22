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
public:
	Cartel(Scene* scene,_ecs::_ingredients_id ingId, Vector pos, float w, float h,Vector triP, float triW, float triH) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h, 0, true); //renderizar el cartel
		new Image(this,to_string(ingId)); //renderizar el cartel
		new CartelTrigger(this, triP-pos, w, h); //pos relativa
	};
};

