#include "MainMenu.h"
#include "../structure/SceneManager.h"
#include "../scenes/Restaurant.h"
#include "../components/Transform.h"
#include "../components/Image.h"

#include "../utils/checkML.h"

void MainMenu::start() {
	SceneManager::instance()->setResize();
	SceneManager::instance()->changeScene(new Restaurant());
}

MainMenu::MainMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/mainMenuTemp.png");
	new Image(bg, image);

	button = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 2 * SDLUtils::instance()->height() / 5), 385, 130, start);
}

MainMenu::~MainMenu() {
	delete image;
}

void MainMenu::handleEvents(){
	if (ih->isKeyDown(SDLK_1)) {
		SceneManager::instance()->changeScene(new DailyMenuScene());
	}
	else if (ih->isKeyDown(SDLK_2)) {
		SceneManager::instance()->setResize();
		SceneManager::instance()->changeScene(new SuperMarket());
	}
	else {
		Scene::handleEvents();
	}
}