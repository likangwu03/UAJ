#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "Restaurant.h"
#include "UIRestaurant.h"
#include "../Structure/GameManager.h"

#include "../Utilities/checkML.h"

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64) {
	init();
}

void DailyMenuScene::buttonPress() {
	GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
	GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
	GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
	executed = true;
}

void DailyMenuScene::init() {
	executed = false;
	dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8 - DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[&]() { 
			if (!executed) {
				GameManager::get()->setTodaysMenu(dailyMenu1->getComponent<DailyMenuComp>()->getMenu());
				buttonPress();
			}
		});

	dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2 + DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[&]() { 
			if (!executed) {
				GameManager::get()->setTodaysMenu(this->dailyMenu2->getComponent<DailyMenuComp>()->getMenu());
				buttonPress();
			}
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
	executed = false;
}
