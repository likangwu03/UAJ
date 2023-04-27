#include "CoopMenu.h"
#include "../../Structure/GameManager.h"
#include "../GameScenes/DailyMenuScene.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../../Components/Text2.h"
#include "../GameScenes/BeforeDayStartScene.h"
#include "../../Utilities/checkML.h"
#include "../../Structure/Game.h"
#include "../../Utilities/CoopHandler.h"
#include "../../Components/Textbox.h"


CoopMenu::CoopMenu() {

	text = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	text_ip = new Font("assets/Fonts/chary___.ttf", 40);
	waiting = new Texture(sdlutils().renderer(), "Waiting for other player", *text, build_sdlcolor(0x000000FF));
	button = 0;

	server = true;
	wait = false;
	enterIp_ = false;

	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("CONTINUE_BG"));

	new Image(bg, image);
	textBox = new Texture(sdlutils().renderer(), "assets/Sprites/UI/textbox.png");

	IP = new GameObject(this);
	new Transform(IP, { (float)(SDLUtils::instance()->width() / 2) - 385 / 2, (float)SDLUtils::instance()->height() / 4 - 130 / 2 }, { 0,0 }, 385, 100);
	new Image(IP, textBox);
	new Text2(IP, "localhost", text_ip);
	new TextBox(IP, "BUTTON2_HIGHLIGHT");

	IP->getComponent<Text2>()->Setoffset(Vector(50, 20));
	IP->setActives(false);

	coop = Game::instance()->getCoopHandler();

	buttonServer = new ButtonGO(this, "HOST_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() / 4 - 130 / 2), 385, 130,
		[&]() {
			try {
				coop->openServer();
				wait = true;
				server = true;
				onWaiting();
			}
			catch (exception e) {
				wait = false;
			}
		});

	buttonServer->getComponent<ButtonComp>()->setHighlighted(true);
	buttonClient = new ButtonGO(this, "JOIN_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 2 / 4 - 130 / 2), 385, 130,
		[&]()
		{
			server = false;
			enterIp();

		});

	buttonResume = new ButtonGO(this, "RETURN_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 3 / 4 - 130 / 2), 385, 130,
		[&]() {
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), true);
		});


	buttonResume2 = new ButtonGO(this, "RETURN_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 3 / 4 - 130 / 2), 385, 130,
		[&]() {
			goBack();
		});

	buttonConfir = new ButtonGO(this, "JOIN_BUTTON", "BUTTON2_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 2 / 4 - 130 / 2), 385, 130,
		[&]()
		{
			try {
				coop->openClient(IP->getComponent<Text2>()->getText_());
				wait = true;
				server = false;
			}
			catch (exception e) {
				wait = false;
			}
		});

	buttonResume2->setActives(false);


	buttonConfir->setActives(false);
}


CoopMenu::~CoopMenu() {
	delete text;
	delete waiting;
	delete text_ip;
	delete textBox;
}



void CoopMenu::update() {
	if (wait) {
		if (server && coop->connectClient()) {
			GameManager::get()->newGame();
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART));
			Game::instance()->runCoop();
		}
		else if (!server) {
			pair<bool, bool> connect = coop->connectServer();
			if (connect.first && connect.second) {
				GameManager::get()->newGame();
				GameManager::get()->changeScene(GameManager::get()->getScene(sc_BEFOREDAYSTART));
				Game::instance()->runCoop();
			}
			else if (connect.first || connect.second) {
				// CAMBIAR
				throw std::exception("Server not ok.");
				//mejor aqui salir de wait y entra a introducir ip
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
	if (!wait && !enterIp_) {
		buttonServer->getComponent<ButtonComp>()->setHighlighted(selected == 0);
		buttonClient->getComponent<ButtonComp>()->setHighlighted(selected == 1);
		buttonResume->getComponent<ButtonComp>()->setHighlighted(selected == 2);
	}
	else if (enterIp_) {
		IP->getComponent<TextBox>()->setHighlighted(selected == 0);
		buttonConfir->getComponent<ButtonComp>()->setHighlighted(selected == 1);
		buttonResume2->getComponent<ButtonComp>()->setHighlighted(selected == 2);
	}

}



void CoopMenu::onWaiting() {
	ih->refresh();
	buttonServer->setActives(false);
	buttonClient->setActives(false);
	buttonResume->setActives(false);
	buttonResume2->setActives(true);
	buttonResume2->getComponent<ButtonComp>()->setHighlighted(true);
}

void CoopMenu::enterIp() {
	ih->refresh();
	IP->getComponent<TextBox>()->setHighlighted(true);
	buttonServer->setActives(false);
	buttonClient->setActives(false);
	buttonResume->setActives(false);
	IP->setActives(true);
	buttonResume2->setActives(true);
	buttonConfir->setActives(true);
	enterIp_ = true;
}


void CoopMenu::goBack() {
	coop->closeServer();
	IP->setActives(false);
	buttonServer->setActives(true);
	buttonClient->setActives(true);
	buttonResume->setActives(true);
	buttonResume2->setActives(false);
	buttonConfir->setActives(false);
	wait = false;
	enterIp_ = false;

}