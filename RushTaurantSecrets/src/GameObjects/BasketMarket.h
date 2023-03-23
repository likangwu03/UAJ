#pragma once
#include "../Structure/GameObject.h"
#include "../Components/BasketMarketComponent.h"

// gestiona la cesta en el supermercado
class BasketMarket : public GameObject {
private:
	BasketMarketComponent* basketMC;
public:
	BasketMarket(Scene* scene) : GameObject(scene, _ecs::grp_ICONS, _ecs::hdr_SM_INVENTORY) {
		basketMC = new BasketMarketComponent(this);
	}
};