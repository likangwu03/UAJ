#pragma once
#include "../Components/InventoryComp.h"
#include "../Structure/GameObject.h"
/*se encarga de gestionar la lista de platos a servir y de renderizar el inventario*/
class Inventory:public GameObject
{
public:
	Inventory(Scene* scene):GameObject(scene, _ecs::grp_ICONS) {
		new InventoryComp(this);
		
	};
};

