#pragma once
#include "../structure/GameObject.h"
#include "../components/DishCombComp.h"
using namespace std;
/*
* Sirve para consultar el plato que puede generar seg¨²n la combinaci¨®n de una serie ingredientes
* Se crea solo una vez en Escena
*/
class DishCombinator:public GameObject
{

public:
	DishCombinator(Scene* scene):GameObject(scene, _ecs::grp_GENERAL) {
		new DishCombComp(this);
	};
};

