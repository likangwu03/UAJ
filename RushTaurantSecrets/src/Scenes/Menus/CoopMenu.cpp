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

	text_ip = new Font("assets/Fonts/chary___.ttf", 40);
	waiting = new Texture(sdlutils().renderer(), "Waiting for the ", *text_ip, build_sdlcolor(0x513a2bFF));
	waiting2= new Texture(sdlutils().renderer(), "other player...", *text_ip, build_sdlcolor(0x513a2bFF));
	button = 0;

	server = true;
	wait = false;
	enterIp_ = false;

	bg = new GameObject(this);
	new Transform(bg, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	image = &(sdlutils().images().at("CONTINUE_BG"));

	new Image(bg, image);
	textBox = &(sdlutils().images().at("TEXTBOX"));

	IP = new GameObject(this);
	new Transform(IP, { (float)(SDLUtils::instance()->width() / 2) - 385 / 2, (float)SDLUtils::instance()->height() / 4 - 130 / 2 }, { 0,0 }, 385, 100);
	new Image(IP, textBox);
	new Text2(IP, "localhost", text_ip);
	new TextBox(IP, "BUTTON_HIGHLIGHT");

	IP->getComponent<Text2>()->Setoffset(Vector(50, 20));
	IP->setActives(false);

	coop = Game::instance()->getCoopHandler();

	buttonServer = new ButtonGO(this, "HOST_BUTTON", "BUTTON_HIGHLIGHT",
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
	buttonClient = new ButtonGO(this, "JOIN_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 2 / 4 - 130 / 2), 385, 130,
		[&]()
		{
			server = false;
			enterIp();

		});

	buttonResume = new ButtonGO(this, "RETURN_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 3 / 4 - 130 / 2), 385, 130,
		[&]() {
			GameManager::get()->changeScene(GameManager::get()->getScene(sc_MAINMENU), true);

		});


	buttonResume2 = new ButtonGO(this, "RETURN_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 3 / 4 - 130 / 2), 385, 130,
		[&]() {
			goBack();
		});

	buttonConfir = new ButtonGO(this, "JOIN_BUTTON", "BUTTON_HIGHLIGHT",
		Vector((SDLUtils::instance()->width() / 2) - 385 / 2, SDLUtils::instance()->height() * 2 / 4 - 130 / 2), 385, 130,
		[&]()
		{
			try {
				coop->openClient(IP->getComponent<Text2>()->getText_());
				wait = true;
				server = false;
				buttonConfir->setActives(false);
				IP->setActives(false);
				buttonResume2->getComponent<ButtonComp>()->setHighlighted(true);
				button = 2;
			}
			catch (exception e) {
				wait = false;
			}
		});

	buttonResume2->setActives(false);


	buttonConfir->setActives(false);
}


CoopMenu::~CoopMenu() {
	delete waiting;
	delete waiting2;
	delete text_ip;
}



void CoopMenu::render() {
	Scene::render();
	if (wait)
	{
		waiting->render(build_sdlrect(WIDTH / 2 - 385 / 2, HEIGHT / 2 - 180, 385, 80));
		waiting2->render(build_sdlrect(WIDTH / 2 - 385 / 2, HEIGHT / 2-80, 385, 80));
	}
}



void CoopMenu::update() {
	if (wait) {
		if (server && coop->connectClient()) {
			GameManager::get()->newGame();
			GameManager::get()->getScene(sc_MAINMENU)->haltSound();

			GameManager::get()->initCoopMode(server);
			Game::instance()->runCoop();
			GameManager::get()->quitCoopMode();
		}
		else if (!server) {
			pair<bool, bool> connect = coop->connectServer();;
			if (connect.first && connect.second) {
				GameManager::get()->newGame();
				GameManager::get()->getScene(sc_MAINMENU)->haltSound();
				GameManager::get()->initCoopMode(server);
				Game::instance()->runCoop();
				GameManager::get()->quitCoopMode();
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
		//ih->refresh();
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_UP)
			|| ih->getHatStateMenu(UP)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_DOWN)
			|| ih->getHatStateMenu(DOWN)) {
			button = (button + 1) % NUM_BUTTON;
			selectedButton(button);
		}
	}
	else {
		if (ih->isKeyDown(SDLK_UP)) {
			button = (button - 1) % NUM_BUTTON;
			if (button < 0)
				button = button + NUM_BUTTON;
			selectedButton(button);
		}
		else if (ih->isKeyDown(SDLK_DOWN) ) {
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
	button = 0;
	buttonResume2->getComponent<ButtonComp>()->setHighlighted(false);
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