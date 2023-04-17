#include "ContinueMenu.h"
#include "../../Structure/GameManager.h"
#include "../GameScenes/DailyMenuScene.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../../Utilities/checkML.h"


void ContinueMenu::bResume() {
	GameManager::get()->popScene();
}

void ContinueMenu::bNewGame() {
	GameManager::get()->newGame();
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
	GameManager::get()->getDailyMenu()->reset();
}
void ContinueMenu::bContinue() {
	GameManager::get()->load();
	GameManager::get()->getBeforeDayStart()->reset();
	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
	GameManager::get()->getDailyMenu()->reset();
}

ContinueMenu::ContinueMenu() {
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(bg, image);
	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.5 * SDLUtils::instance()->height()*2 / 5), 385, 130, bResume);
	buttonNewGame = new ButtonGO(this, "1_PLAYER_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2)-250, 1.5 * SDLUtils::instance()->height() / 5), 385, 130, bNewGame);
	buttonContinue = new ButtonGO(this, "2_PLAYER_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2)+250, 1.5 * SDLUtils::instance()->height() / 5), 385, 130, bContinue);
}

ContinueMenu::~ContinueMenu() {
	delete image;
}
