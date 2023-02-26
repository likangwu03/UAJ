#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/KitchenIslandTrigger.h"
#include "../components/KitchenIslandComp.h"
#include "../components/Image.h"

using namespace std;
class KitchenIsland :public GameObject
{
public:
	KitchenIsland(Scene* scene, vector<pair<_ecs::_ingredients_id,int>>ing, Vector pos, float w, float h/*, Vector triP, float triW, float triH*/) :GameObject(scene, _ecs::grp_INTERACTABLE,_ecs::hdr_KITCHENISLAND) {
		new Transform(this, pos, Vector(0, 0), w, h, 0, true); //para saber en qu¨¦ posici¨®n renderizar el bocadillo 
	//	new Image(this, "ISLAND_HIGHLIGHT"); 
		new KitchenIslandComp(this,ing);
	};
};