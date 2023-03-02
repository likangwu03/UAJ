#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "../utils/checkML.h"
#include "../structure/SceneManager.h"

void DailyMenuScene::select()
{
	SceneManager::instance()->changeScene(new SuperMarket(), 1);
}

DailyMenuScene::DailyMenuScene(uint8_t msize, bool m) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64)
{
	DailyMenu* dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8, sdl->height() / 15), 451.0f, 603.0f, select);
	DailyMenu* dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2, sdl->height() / 15), 451.0f, 603.0f, select);

	//ButtonGO* dailyMenu2 = new ButtonGO(this, Vector(sdl->width() / 2, sdl->height() / 15), 451, 603);
}

void DailyMenuScene::handleEvents() {
	Scene::handleEvents();
}
