#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "Restaurant.h"
#include "UIRestaurant.h"
#include "../Structure/GameManager.h"

#include "../Utilities/checkML.h"

void DailyMenuScene::select1() {
	GameManager::get()->changeScene(GameManager::get()->getSupermarket());
}

void DailyMenuScene::select2() {
	GameManager::get()->changeScene(GameManager::get()->getSupermarket());
}

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64) {
	init();
}


void DailyMenuScene::init() {

	dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8 - DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[=]() { 
			GameManager::get()->setTodaysMenu(dailyMenu1->getComponent<DailyMenuComp>()->getMenu());
			GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
			GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
		});

	dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2 + DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[=]() { 
			GameManager::get()->setTodaysMenu(dailyMenu2->getComponent<DailyMenuComp>()->getMenu());
			GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
			GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
		});
}


void DailyMenuScene::update() {
	if (changeMenu) {
		changeMenu = false;
		init();
	}
}


void DailyMenuScene::reset() {
	if (dailyMenu1 != nullptr) dailyMenu1->setAlive(false);
	if (dailyMenu2 != nullptr) dailyMenu1->setAlive(false);
	changeMenu = true;
}
