#include "ContinueMenu.h"
#include "../../Structure/GameManager.h"
#include "../GameScenes/DailyMenuScene.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../Cutscenes/IntroScene.h"
#include "../../Utilities/checkML.h"


ContinueMenu::ContinueMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/street_bg.png");
	new Image(bg, image);
	buttonMainMenu = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.5 * SDLUtils::instance()->height()*2 / 5), 385, 130, 
		[&] {
			GameManager::get()->getMainMenu();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getMainMenu());
		});
	buttonNewGame = new ButtonGO(this, "NEWGAME_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2) - 250, 1.5 * SDLUtils::instance()->height() / 5), 385, 130, 
		[&] {
			GameManager::get()->newGame();
			GameManager::get()->changeScene(GameManager::get()->getIntroScene(), true);
			GameManager::get()->getCurrentScene()->callAfterCreating();
		});
	buttonContinue = new ButtonGO(this, "CONTINUE_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2)+250, 1.5 * SDLUtils::instance()->height() / 5), 385, 130, 
		[&] {
			GameManager::get()->load();
			GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
		});
}

ContinueMenu::~ContinueMenu() {
	delete image;
}
