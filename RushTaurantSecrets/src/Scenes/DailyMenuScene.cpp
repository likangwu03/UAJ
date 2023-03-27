#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "Restaurant.h"
#include "UIRestaurant.h"
#include "../Structure/GameManager.h"

#include "../Utilities/checkML.h"

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64), executed(false) {
	init();
}

void DailyMenuScene::buttonPress() {
	GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
	GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
	GameManager::get()->getSupermarket()->reset();
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


void DailyMenuScene::reset() {
	DailyMenu* aux1 = dailyMenu1;
	DailyMenu* aux2 = dailyMenu2;
	aux1->setAlive(false);
	aux2->setAlive(false);
	init();
}
