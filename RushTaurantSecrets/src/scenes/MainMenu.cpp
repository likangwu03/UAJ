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
	image = new Texture(sdlutils().renderer(), "assets/mainMenu_bg.png");
	new Image(bg, image);

	oneplayer = new ButtonGO(this, "PLAY_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 2.6 * (192 * 2 / 2), 2.7 * SDLUtils::instance()->height() / 5), 395, 130, start);
	options = new ButtonGO(this, "OPTIONS_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 2.6 * (192 * 2 / 2), 3.7 * SDLUtils::instance()->height() / 5), 395, 130, opt);
}

MainMenu::~MainMenu() {
	delete image;
}

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