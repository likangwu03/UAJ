#pragma once
#include "../components/InventoryComp.h"
#include "../structure/GameObject.h"
/*se encarga de gestionar la lista de platos a servir y de renderizar el inventario*/
class Inventory:public GameObject
{
public:
	Inventory(Scene* scene):GameObject(scene, _ecs::grp_HUD, _ecs::hdr_INVENTORY) {
		new InventoryComp(this);
		//hay que añadir otros componentes para renderizar el inventario,etc...
		
	};
};

