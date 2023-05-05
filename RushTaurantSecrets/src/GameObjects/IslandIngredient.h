#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/KitchenIslandTrigger.h"

using namespace std;
/*para los ingredientes de la mesa*/
class IslandIngredient :public GameObject
{
public:
	IslandIngredient(Scene* scene, Vector pos, float w, float h,int i,int orient) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h, 0, true); //para saber en que posicion renderizar el bocadillo 
		new KitchenIslandTrigger(this,{0,0},w,h,i,orient);
	};
};