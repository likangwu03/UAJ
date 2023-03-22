#include "MainMenu.h"

#include "../structure/Scene.h"
#include "../gameObjects/ButtonGO.h"
#include "../sdlutils/Texture.h"

#include "../structure/GameManager.h"
#include "../scenes/Restaurant.h"
#include "../scenes/DailyMenuScene.h"
#include "../scenes/OptionsMenu.h"
#include "../components/Transform.h"
#include "../components/Image.h"

#include "../utils/checkML.h"

void MainMenu::start() {
	GameManager::get()->changeScene(GameManager::get()->getRestaurant());
}

void MainMenu::opt() {
	GameManager::get()->changeScene(GameManager::get()->getOptionsMenu());
}

MainMenu::MainMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("MAIN_MENU_BG"));
	new Image(bg, image);

	oneplayer = new ButtonGO(this, "1_PLAYER_BUTTON", "BUTTON2_HIGHLIGHT", Vector(BUTTONS_X, BUTTONS_Y), BUTTONS_W, BUTTONS_H, start);
	twoplayer = new ButtonGO(this, "2_PLAYER_BUTTON", "BUTTON2_HIGHLIGHT", Vector(BUTTONS_X, BUTTONS_Y + 1.1 * BUTTONS_H), BUTTONS_W, BUTTONS_H, start);
	options = new ButtonGO(this, "OPTIONS_BUTTON", "BUTTON2_HIGHLIGHT", Vector(BUTTONS_X, BUTTONS_Y + 2.1 * BUTTONS_H), BUTTONS_W, BUTTONS_H, opt);
}

MainMenu::~MainMenu() { }

void MainMenu::handleEvents(){
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
	}
	else if (ih->isKeyDown(SDLK_2)) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getSupermarket());
	}
	else {
		Scene::handleEvents();
	}
}