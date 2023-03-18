#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "../utils/checkML.h"
#include "../structure/GameManager.h"

void DailyMenuScene::select1()
{
	GameManager::instance()->changeScene(GameManager::instance()->getSupermarket());
}

void DailyMenuScene::select2()
{
	GameManager::instance()->changeScene(GameManager::instance()->getSupermarket());
}

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64)
{
	init();
}

void DailyMenuScene::handleEvents() {
	Scene::handleEvents();
}

void DailyMenuScene::init()
{
	dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8, sdl->height() / 15), 479.0f, 640.0f,
		[&]() { 
			GameManager::instance()->setTodaysMenu(dailyMenu1->getComponent<DailyMenuComp>()->getMenu());
			GameManager::instance()->changeScene((Scene*)GameManager::instance()->getSupermarket());
		});

	dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2, sdl->height() / 15), 479.0f, 640.0f,
		[&]() { 
			GameManager::instance()->setTodaysMenu(dailyMenu2->getComponent<DailyMenuComp>()->getMenu());
			GameManager::instance()->changeScene((Scene*)GameManager::instance()->getSupermarket());
		});
}
