#include "CoopMenu.h"
#include "../../Structure/GameManager.h"
#include "../GameScenes/DailyMenuScene.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../../Utilities/checkML.h"
#include "../../Structure/Game.h"
#include "../../Utilities/CoopHandler.h"


void CoopMenu::bResume() {
	GameManager::get()->popScene();
}

void CoopMenu::bServer() {
	Game::instance()->getCoopHandler()->openServer();
}
void CoopMenu::bClient() {
	
}
void CoopMenu::init() {

}
CoopMenu::CoopMenu() {
	server = true;
	wait = false;
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(bg, image);
	
	coop = Game::instance()->getCoopHandler();
	buttonResume = new ButtonGO(this, "RESUME_BUTTON_UP", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2), 1.5 * SDLUtils::instance()->height() * 2 / 5), 385, 130, bResume);
	buttonServer = new ButtonGO(this, "1_PLAYER_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2) - 250, 1.5 * SDLUtils::instance()->height() / 5), 385, 130, [&]()
		{
			wait = true;
			server = true;
			coop->openServer();
		});
	buttonClient = new ButtonGO(this, "2_PLAYER_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - (192 * 2 / 2) + 250, 1.5 * SDLUtils::instance()->height() / 5), 385, 130,
		[&]()
		{
			wait = true;
			server = false;
			coop->openClient(ip);
		});


	text = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	waiting = new Texture(sdlutils().renderer(), "Waiting for other player", *text, build_sdlcolor(0x000000FF));

}


CoopMenu::~CoopMenu() {
	delete image;
	delete text;
	delete waiting;
}



void CoopMenu::update(){
	if (wait) {
		if (server && coop->connectClient()) {
			GameManager::get()->newGame();
			GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
			GameManager::get()->getDailyMenu()->reset();

			Game::instance()->runCoop();
		}
		else if (!server) {

			pair<bool, bool> connect = coop->connectServer();
			if (connect.first && connect.second) {
				GameManager::get()->newGame();
				GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
				GameManager::get()->getDailyMenu()->reset();
				Game::instance()->runCoop();
			}
			else if (connect.first || connect.second) {
				// CAMBIAR
				throw std::exception("Server not ok.");
			}
		}
	}
	Scene::update();
	
}