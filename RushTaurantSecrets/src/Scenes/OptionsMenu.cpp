#include "OptionsMenu.h"
#include "../Structure/GameManager.h"

#include "../Utilities/checkML.h"

void OptionsMenu::mMenu() {
	GameManager::get()->changeScene((Scene*)GameManager::get()->getMainMenu());
}

void OptionsMenu::bResume() {
	GameManager::get()->popScene();
}

OptionsMenu::OptionsMenu() : sdl(SDLUtils::instance()), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(bg, image);

	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.5 * SDLUtils::instance()->height() / 5), 385, 130, bResume);
	supermarketMusic->setMusicVolume(MUSIC_VOL);
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
		supermarketMusic->play();
	}
	else {
		Scene::handleEvents();
	}
}