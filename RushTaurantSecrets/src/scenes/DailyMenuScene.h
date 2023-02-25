#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/Structure_def.h"
#include "../structure/GameObject.h"
#include "../structure/SceneManager.h"
#include "../gameObjects/ButtonGO.h"

using namespace std;

class DailyMenuScene : public Scene
{
	SDLUtils* sdl;
	uint8_t menuSize;
	uint8_t spriteSize;
	static void select(SceneManager* sceneManager);
public:
	DailyMenuScene(SceneManager* sceneManager, uint8_t msize = 4, bool m = true);
	//cambiar esto a supermarket cuando exista xdd
	void handleEvents();
};

