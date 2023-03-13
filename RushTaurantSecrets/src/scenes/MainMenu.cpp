#include "MainMenu.h"

#include "../structure/Scene.h"
#include "../gameObjects/ButtonGO.h"
#include "../sdlutils/Texture.h"

#include "../structure/GameManager.h"
#include "../scenes/Restaurant.h"
#include "../components/Transform.h"
#include "../components/Image.h"

#include "../utils/checkML.h"

void MainMenu::start() {
	GameManager::instance()->changeScene(GameManager::instance()->getRestaurant());
}

MainMenu::MainMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/mainMenuTemp.png");
	new Image(bg, image);

	button = new ButtonGO(this, "PLAY_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2 * SDLUtils::instance()->height() / 5), 385, 130, start);
}

MainMenu::~MainMenu() {
	delete image;
}

void MainMenu::handleEvents(){
	if (ih->isKeyDown(SDLK_1)) {
		GameManager::instance()->changeScene(GameManager::instance()->getDailyMenu());
	}
	else if (ih->isKeyDown(SDLK_2)) {
		GameManager::instance()->changeScene(GameManager::instance()->getSupermarket());
	}
	else {
		Scene::handleEvents();
	}
}