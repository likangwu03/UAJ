#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "Restaurant.h"
#include "../HUD/UIRestaurant.h"
#include "../../Structure/GameManager.h"

#include "../../Utilities/checkML.h"

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	background = new GameObject(this);
	new Transform(background, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("DAILY_MENU_BG"));
	new Image(background, image);
	dailyMenu1 = dailyMenu2 = nullptr;
	supermarketMusic->setMusicVolume(MUSIC_VOL);
}

void DailyMenuScene::buttonPress() {
	GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
	GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
	GameManager::get()->getSupermarket()->reset();
	GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
	supermarketMusic->play();
}

void DailyMenuScene::init() {
	SDL_SetRenderDrawColor(sdl->renderer(), 170, 121, 89, 255);
	SDL_RenderClear(sdl->renderer());
	SDL_RenderPresent(sdl->renderer());
	dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8 - DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[&]() {
			GameManager::get()->setTodaysMenu(dailyMenu1->getComponent<DailyMenuComp>()->getMenu());
			buttonPress();
		});
	dailyMenu1->getComponent<DailyMenuComp>()->initMenu();
	dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2 + DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[&]() {
			GameManager::get()->setTodaysMenu(this->dailyMenu2->getComponent<DailyMenuComp>()->getMenu());
			buttonPress();
		});
	dailyMenu2->getComponent<DailyMenuComp>()->initMenu();
}


void DailyMenuScene::reset() {
	if (dailyMenu1 != nullptr) {
		dailyMenu1->setAlive(false);
		dailyMenu2->setAlive(false);
	}
	init();
}
