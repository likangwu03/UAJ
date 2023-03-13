#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "../utils/checkML.h"
#include "../structure/GameManager.h"

void DailyMenuScene::select()
{
	GameManager::instance()->changeScene(GameManager::instance()->getSupermarket());
}

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64)
{
	DailyMenu* dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8, sdl->height() / 15), 479.0f, 640.0f, select);
	DailyMenu* dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2, sdl->height() / 15), 479.0f, 640.0f, select);

	//ButtonGO* dailyMenu2 = new ButtonGO(this, Vector(sdl->width() / 2, sdl->height() / 15), 451, 603);
}

void DailyMenuScene::handleEvents() {
	Scene::handleEvents();
}
