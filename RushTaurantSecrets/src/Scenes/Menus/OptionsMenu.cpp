#include "OptionsMenu.h"
#include "../../Structure/GameManager.h"

#include "../../Utilities/checkML.h"


OptionsMenu::OptionsMenu() : sdl(SDLUtils::instance()), supermarketMusic(&sdl->musics().at("SUPERMARKET_MUSIC")) {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(bg, image);

	buttonReturn = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.5 * SDLUtils::instance()->height() / 5), 385, 130, 
		[&]() {
			GameManager::get()->popScene();
		});
	
	supermarketMusic->setMusicVolume(MUSIC_VOL);

	//[&]() {
	//	GameManager::get()->changeScene((Scene*)GameManager::get()->getMainMenu());
	//});
}

OptionsMenu::~OptionsMenu() {
	delete image;
}

