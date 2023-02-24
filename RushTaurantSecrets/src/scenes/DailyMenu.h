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

class DailyMenu : public Scene
{
	bool murder;
	SDLUtils* sdl = SDLUtils::instance();
	vector<_ecs::DishInfo> menu1;
	vector<_ecs::DishInfo> menu2;
	vector<_ecs::DishInfo> randomMenu();
	void drawDishes(GameObject* d, vector<_ecs::DishInfo> menu);
	uint8_t menuSize;
	uint8_t spriteSize;
	static void select(SceneManager* sceneManager);
	SDL_Rect src, dest;
public:
	DailyMenu(SceneManager* sceneManager, uint8_t msize = 4, bool m = true);
	//cambiar esto a supermarket cuando exista xdd
	void handleEvents();
};

