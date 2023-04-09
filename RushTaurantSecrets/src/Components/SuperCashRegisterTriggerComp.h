#pragma once
#include "../Structure/TriggerComp.h"
#include "InventoryComp.h"
#include "Image.h"
#include "../Managers/Money.h"
#include "../GameObjects/BasketMarket.h"
#include "../Components/BasketMarketComponent.h"

class SuperCashRegisterTriggerComp : public TriggerComp
{
private:
	const int MUSIC_VOL = 30;

	Image* highlight;
	Money* money;

	BasketMarket* bM = nullptr;
	BasketMarketComponent* bMC = nullptr;

	SDLUtils* sdl;
	Music* restaurantMusic;

public:
	SuperCashRegisterTriggerComp(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();
	virtual void onTriggerExit();

private:
	void payAndLeave();
};

