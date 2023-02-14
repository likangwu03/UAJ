#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
//#include "../objects/Money.h"
//#include "../objects/Inventory.h"

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	//Inventory inventory;
	SDLUtils* sdl = SDLUtils::instance();
	//Money* money = Money::Instance();
	int x = 0, y = 0,
		winH = sdl->height(), winW = sdl->width();

public:
	UIRestaurant();
	void showMoneyText();
};

