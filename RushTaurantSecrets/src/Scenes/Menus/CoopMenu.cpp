#include "CoopMenu.h"
#include "../../Structure/GameManager.h"
#include "../GameScenes/DailyMenuScene.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../../Utilities/checkML.h"
#include "../../Structure/Game.h"
#include "../../Utilities/CoopHandler.h"


CoopMenu::CoopMenu() {
	server = true;
	wait = false;
	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("CONTINUE_BG"));

	new Image(bg, image);
	
	coop = Game::instance()->getCoopHandler();
	buttonServer = new ButtonGO(this, "HOST_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() / 4 - 130 / 2), 385, 130, 
		[&]() {
			wait = true;
			server = true;
			coop->openServer();
		});
	buttonServer->getComponent<ButtonComp>()->setHighlighted(true);
	buttonClient = new ButtonGO(this, "JOIN_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 2 / 4 - 130 / 2), 385, 130,
		[&]()
		{
			wait = true;
			server = false;
			coop->openClient(ip);
		});

	buttonResume = new ButtonGO(this, "RETURN_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 3 / 4 - 130 / 2), 385, 130,
		[&]() {
			GameManager::get()->changeScene((Scene*)GameManager::get()->getMainMenu(), false);
		});

	text = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	waiting = new Texture(sdlutils().renderer(), "Waiting for other player", *text, build_sdlcolor(0x000000FF));
	button = 0;

}


CoopMenu::~CoopMenu() {
	delete text;
	delete waiting;
}



void CoopMenu::update(){
	if (wait) {
		if (server && coop->connectClient()) {
			GameManager::get()->newGame();
			GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
			Game::instance()->runCoop();
		}
		else if (!server) {

			pair<bool, bool> connect = coop->connectServer();
			if (connect.first && connect.second) {
				GameManager::get()->newGame();
				GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
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

void CoopMenu::handleEvents() {

	if (ih->joysticksInitialised()) {
		ih->refresh();
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
			|| ih->getHatState(UP)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			|| ih->getHatState(DOWN)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	else {
		if (ih->isKeyDown(SDL_SCANCODE_W)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->isKeyDown(SDL_SCANCODE_S)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	Scene::handleEvents();
}

void CoopMenu::selectedButton(int selected) {
	buttonServer->getComponent<ButtonComp>()->setHighlighted(false);
	buttonClient->getComponent<ButtonComp>()->setHighlighted(false);
	buttonResume->getComponent<ButtonComp>()->setHighlighted(false);
	switch (selected)
	{
	case 0:
		buttonServer->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 1:
		buttonClient->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 2:
		buttonResume->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	}
}
