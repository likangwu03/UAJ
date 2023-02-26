#pragma once
#include "../structure/GameObject.h"
#include "../components/BasketMarketComponent.h"

// gestiona la cesta en el supermercado
class BasketMarket : public GameObject {
private:
	bool basketON;
public:
	BasketMarket(Scene* scene) : GameObject(scene, _ecs::grp_ICONS, _ecs::hdr_SM_INVENTORY) {
		new BasketMarketComponent(this);
		basketON = false;
	}

	void setBasketON(bool value) { 
		basketON = value;
	}

	bool getBasketON() {
		return basketON;
	}
};