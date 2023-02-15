#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
//#include "../objects/Inventory.h"

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	//Inventory inventory;
	SDLUtils* sdl = SDLUtils::instance();

public:
	UIRestaurant();
	void showMoneyText();
};

