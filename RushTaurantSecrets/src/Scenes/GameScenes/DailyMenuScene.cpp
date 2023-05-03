#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "Restaurant.h"
#include "../HUD/UIRestaurant.h"
#include "../../Structure/GameManager.h"
#include "../../Structure/Game.h"
#include "../../Utilities/checkML.h"

DailyMenuScene::DailyMenuScene(uint8_t msize) : sdl(SDLUtils::instance()), menuSize(msize), spriteSize(64), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	background = new GameObject(this);
	new Transform(background, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("DAILY_MENU_BG"));
	new Image(background, image);
	dailyMenu1 = dailyMenu2 = nullptr;
	supermarketMusic->setMusicVolume(MUSIC_VOL);
}

void DailyMenuScene::buttonPress(int menu) {
	if (menu == 0)GameManager::get()->setTodaysMenu(dailyMenu1->getComponent<DailyMenuComp>()->getMenu());
	else GameManager::get()->setTodaysMenu(dailyMenu2->getComponent<DailyMenuComp>()->getMenu());
	Message m;
	m.id = Message::msg_TO_SUPERMARKET;
	m.daily_menu.menu = menu;
	Game::get()->getCoopHandler()->send(m);
	GameManager::get()->getRestaurant()->getUI()->setDailyMenu();
	GameManager::get()->getSupermarket()->getUI()->setDailyMenu();
	GameManager::get()->changeScene(GameManager::get()->getScene(_ecs::sc_SUPERMARKET));
	supermarketMusic->play(-1);
}

void DailyMenuScene::init() {
	SDL_SetRenderDrawColor(sdl->renderer(), 170, 121, 89, 255);
	SDL_RenderClear(sdl->renderer());
	SDL_RenderPresent(sdl->renderer());
	dailyMenu1 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 8 - DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[&]() {
			buttonPress(0);
		});
	dailyMenu1->getComponent<DailyMenuComp>()->initMenu();
	dailyMenu2 = new DailyMenu(this, "DAILY_MENU", Vector(sdl->width() / 2 + DISTANCE / 2, POS_Y), 479.0f, 640.0f,
		[&]() {
			buttonPress(1);
		});
	dailyMenu2->getComponent<DailyMenuComp>()->initMenu();

	selectedButton(0);
	button = 0;
	GameManager::get()->getSupermarket()->getUI()->reset();
}


void DailyMenuScene::reset() {
	if (dailyMenu1 != nullptr) {
		dailyMenu1->setAlive(false);
		dailyMenu2->setAlive(false);
	}
	init();
}

void DailyMenuScene::handleEvents() {
	if (ih->joysticksInitialised()) {
		ih->refresh();
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)
			|| ih->getHatState(LEFT) || (ih->xvalue(0, 1) < 0)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
			|| ih->getHatState(RIGHT) || (ih->xvalue(0, 1) > 0)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	else {
		if (ih->isKeyDown(SDL_SCANCODE_LEFT)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->isKeyDown(SDL_SCANCODE_RIGHT)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	if (!active) return;
	Scene::handleEvents();
}

void DailyMenuScene::selectedButton(int selected) {
	dailyMenu1->getComponent<ButtonComp>()->setHighlighted(selected==0);
	dailyMenu2->getComponent<ButtonComp>()->setHighlighted(selected==1);
}

void DailyMenuScene::initCoopMode(bool server) {
	active = server;
}

void DailyMenuScene::quitCoopMode() {
	active = true;
}

void DailyMenuScene::receive(const Message& message) {
	if (message.id == Message::msg_TO_SUPERMARKET) {
		int aux = message.daily_menu.menu;
		buttonPress(aux);
	}

}

void DailyMenuScene::setMenus(const vector<uint8_t>& menu1, const vector<uint8_t>& menu2) {
	dailyMenu1->getComponent<DailyMenuComp>()->initMenu(menu1);
	dailyMenu2->getComponent<DailyMenuComp>()->initMenu(menu2);
}

void DailyMenuScene::getMenus(vector<uint8_t>& menu1, vector<uint8_t>& menu2) {
	auto m1=dailyMenu1->getComponent<DailyMenuComp>()->getMenu();
	auto m2 = dailyMenu2->getComponent<DailyMenuComp>()->getMenu();
	
	for (auto m : *m1) {
		menu1.push_back(m.id);
	}
	for (auto m : *m2) {
		menu2.push_back(m.id);
	}
}