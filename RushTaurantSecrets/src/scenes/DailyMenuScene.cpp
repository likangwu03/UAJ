#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "Restaurant.h"
#include "UIRestaurant.h"
#include "../utils/checkML.h"
#include "../structure/GameManager.h"

void DailyMenuScene::select1()
{
	GameManager::get()->changeScene(GameManager::get()->getSupermarket());
}

void DailyMenuScene::select2()
{
	GameManager::get()->changeScene(GameManager::get()->getSupermarket());
}

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64)
{
	init();
}

void DailyMenuScene::handleEvents() {
	Scene::handleEvents();
}

void DailyMenuScene::init() {
	dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8 - DISTANCE / 2, sdl->height() / 15), 479.0f, 640.0f,
		[=]() { 
			GameManager::get()->setTodaysMenu(dailyMenu1->getComponent<DailyMenuComp>()->getMenu());
			GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
			GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
		});

	dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2 + DISTANCE / 2, sdl->height() / 15), 479.0f, 640.0f,
		[=]() { 
			GameManager::get()->setTodaysMenu(dailyMenu2->getComponent<DailyMenuComp>()->getMenu());
			GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
			GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
		});
}
