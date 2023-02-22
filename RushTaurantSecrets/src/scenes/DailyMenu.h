#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../structure/Food_def.h"
#include "../components/Button.h"
#include <set>

using namespace std;
class Restaurant;

class DailyMenu : public Scene
{
	//cambiar a market
	Restaurant* market;
	bool murder;
	SDLUtils* sdl = SDLUtils::instance();
	vector<_ecs::DishInfo> menu1;
	vector<_ecs::DishInfo> menu2;
	vector<_ecs::DishInfo> randomMenu();
public:
	DailyMenu(bool m);
	//cambiar esto a supermarket cuando exista xdd
	void linkSupermarket(Restaurant* sm);
};

