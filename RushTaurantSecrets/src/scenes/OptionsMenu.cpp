#include "OptionsMenu.h"
#include "../structure/GameManager.h"

#include "../utils/checkML.h"

void OptionsMenu::mMenu() {
	GameManager::get()->changeScene((Scene*)GameManager::get()->getMainMenu());
}

void OptionsMenu::bResume() {
	GameManager::get()->popScene();
}

OptionsMenu::OptionsMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(bg, image);

	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.5 * SDLUtils::instance()->height() / 5), 385, 130, bResume);
}

OptionsMenu::~OptionsMenu() {
	delete image;
}

void OptionsMenu::handleEvents() {
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