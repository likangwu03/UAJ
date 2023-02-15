#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../objects/Money.h" // cambiar cuando se cambie la clase Money
#include <string>
//#include "../objects/Inventory.h"

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	//Inventory inventory;
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt = new Money();

public:
	UIRestaurant();
	void showMoneyText();
	void update();
};

