#include "EndOfDayScene.h"
#include "../../Managers/DayManager.h"
#include "../../Structure/GameManager.h"
#include "../../Managers/Reputation.h"
#include "../../Managers/Money.h"
#include "../Menus/MainMenu.h"
#include "BeforeDayStartScene.h"
#include "../../Structure/Game.h"
#include "../../Utilities/checkML.h"
#include "BeforeDayStartScene.h"


EndOfDayScene::EndOfDayScene() {
	gm = GameManager::instance();
	ih = InputHandler::instance();

	accDay = 0;
	moneyGoal = 0;
	playerReputation = 0;
	playerMoney = 0;
	initPlayerMoney = gm->getBeforeDayStartScene()->getInitMoney(); //Dinero con el que ha empezado el día
	earnedMoney = 0;

	dayM = gm->getDayManager();
	_gameOver = false;

	//objetos de la escena
	//fondo de la escena
	backgroundObj = new GameObject(this);
	new Transform(backgroundObj, { 0,0 }, { 0,0 }, sdlutils().width(), sdlutils().height());
	backgroundT = &(sdlutils().images().at("NIGHT_BG"));
	new Image(backgroundObj, backgroundT);

	//icono reputación
	reputationObj = new GameObject(this);
	new Transform(reputationObj, { 150,150 }, { 0,0 }, 75, 75);
	reputationIconT = &(sdlutils().images().at("REPUTATION_ICON"));
	new Image(reputationObj, reputationIconT);

	moneyObj = new GameObject(this);
	new Transform(moneyObj, { 150, 250 }, { 0,0 }, 75, 75);
	moneyIconT = &(sdlutils().images().at("MONEY_ICON"));
	new Image(moneyObj, moneyIconT);

	//fuente
	font1 = new Font("assets/Fonts/light_pixel-7.ttf", 30);
	font2 = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	TTF_SetFontOutline(font2->getTTFFont(), 1);

	font3 = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	font4 = new Font("assets/Fonts/light_pixel-7.ttf", 70);
	TTF_SetFontOutline(font4->getTTFFont(), 1);

	reputationtext = "YOUR CURRENT REPUTATION IS: " + to_string(playerReputation);
	moneyText = "TODAY YOU EARNED: " + to_string(earnedMoney) + "$";
	bankruptText = "YOU WENT BANKRUPT!";
	noRepText = "THE WHOLE CITY HATES YOUR RESTAURANT...";

	//texturas que cambian cada dia
	reputationTexture = new Texture(sdlutils().renderer(), reputationtext, *font1, build_sdlcolor(0x000000FF));
	reputationOutline = new Texture(sdlutils().renderer(), reputationtext, *font2, build_sdlcolor(0xFFFFFFFF));

	moneyTexture = new Texture(sdlutils().renderer(), moneyText, *font1, build_sdlcolor(0x000000FF));
	moneyOutline = new Texture(sdlutils().renderer(), moneyText, *font2, build_sdlcolor(0xFFFFFFFF));

	//texturas que se mantienen iguales
	bankruptTexture = new Texture(sdlutils().renderer(), bankruptText, *font3, build_sdlcolor(0x000000FF));
	noRepTexture = new Texture(sdlutils().renderer(), noRepText, *font3, build_sdlcolor(0x000000FF));

	bankruptOutline = new Texture(sdlutils().renderer(), bankruptText, *font4, build_sdlcolor(0xFFFFFFFF));
	noRepOutline = new Texture(sdlutils().renderer(), noRepText, *font4, build_sdlcolor(0xFFFFFFFF));

	bankruptRect = build_sdlrect(sdlutils().width() / 2 - bankruptTexture->width() / 2, 400, bankruptTexture->width(), bankruptTexture->height());
	noRepRect = build_sdlrect(sdlutils().width() / 2 - (0.8 * noRepTexture->width()) / 2, 400, 0.8 * noRepTexture->width(), 0.8 * noRepTexture->height());

	//botones
	
	continueButton = new ButtonGO(this, "CONTINUE_BUTTON", "BUTTON_HIGHLIGHT", Vector(BUTTON1_X, BUTTON1_Y), BUTTON_W, BUTTON_H,
		[&]() {
			if (active) {
				Message m;
				m.id = Message::msg_CONTINUE;
				Game::get()->getCoopHandler()->send(m);
			}
			dayM->newDay();
		});
	continueButton->setAlive(false);
	continueButton->getComponent<ButtonComp>()->setHighlighted(true);

	
	mainMenuButton = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON_HIGHLIGHT", Vector(BUTTON2_X, BUTTON2_Y), BUTTON_W, BUTTON_H,
		[&]() {
			if (active) {
				Game::get()->setExitCoop();
				Message m;
				m.id = Message::msg_TO_MAINMENU;
				Game::get()->getCoopHandler()->send(m);
			}
			gm->get()->changeScene((gm->get()->getScene(sc_MAINMENU)));
		});
	mainMenuButton->setAlive(false);
	

	button = 0;
}

EndOfDayScene::~EndOfDayScene() {
	delete font1;
	delete font2;
	delete reputationTexture;
	delete moneyTexture;
	delete bankruptTexture;
	delete noRepTexture;
	delete reputationOutline;
	delete moneyOutline;
	delete bankruptOutline;
	delete noRepOutline;
	delete font3;
	delete font4;
}

void EndOfDayScene::reset() {
	accDay = dayM->getDay();
	moneyGoal = dayM->getDailyObjective();
	playerReputation = gm->getReputation()->getReputation();
	playerMoney = gm->getMoney()->getMoney();
	if (initPlayerMoney <= playerMoney) earnedMoney = playerMoney - initPlayerMoney;
	else earnedMoney = 0;
	initPlayerMoney = gm->getBeforeDayStartScene()->getInitMoney(); //Dinero con el que ha empezado el día

	continueButton->setAlive(false);
	mainMenuButton->setAlive(false);
	
	gameOver();

	reputationtext = "YOUR CURRENT REPUTATION IS: " + to_string(playerReputation);
	moneyText = "TODAY YOU EARNED: " + to_string(earnedMoney) + "$ OUT OF " + to_string(moneyGoal) + "$";

	delete reputationTexture;
	delete moneyTexture;
	delete reputationOutline;
	delete moneyOutline;

	reputationTexture = new Texture(sdlutils().renderer(), reputationtext, *font1, build_sdlcolor(0x000000FF));
	reputationOutline = new Texture(sdlutils().renderer(), reputationtext, *font2, build_sdlcolor(0xFFFFFFFF));

	moneyTexture = new Texture(sdlutils().renderer(), moneyText, *font1, build_sdlcolor(0x000000FF));
	moneyOutline = new Texture(sdlutils().renderer(), moneyText, *font2, build_sdlcolor(0xFFFFFFFF));
}

void EndOfDayScene::render() {
	Scene::render();

	reputationTexture->render({ 250, 175, reputationTexture->width(), reputationTexture->height() });
	moneyTexture->render({ 250, 275, moneyTexture->width(), moneyTexture->height() });

	reputationOutline->render({ 250, 175, reputationTexture->width(), reputationTexture->height() });
	moneyOutline->render({ 250, 275, moneyTexture->width(), moneyTexture->height() });

	gameOver();

	if (!_gameOver) { //el juego no se ha perdido


		continueButton->setAlive(true);
		mainMenuButton->setAlive(true);
	}
	else { //el juego se ha perdido
		continueButton->setAlive(true);
		mainMenuButton->setAlive(true);

		if ((earnedMoney < moneyGoal || playerMoney <= 0) && playerReputation <= 0) 
		{
			bankruptTexture->render(bankruptRect);
			bankruptOutline->render(bankruptRect);

			noRepTexture->render(noRepRect);
			noRepOutline->render(noRepRect);

		}
		else if (earnedMoney < moneyGoal || playerMoney <= 0) {
			bankruptTexture->render(bankruptRect);
			bankruptOutline->render(bankruptRect);
		}
		else if (playerReputation <= 0) {
			noRepTexture->render(noRepRect);
			noRepOutline->render(noRepRect);
		}

	}


}

void EndOfDayScene::gameOver() {
	if (playerReputation <= 0 || earnedMoney < moneyGoal) _gameOver = true;
}


void EndOfDayScene::handleEvents() {

	if (ih->isKeyDown(SDL_SCANCODE_A)) {
		button = (button - 1) % NUM_BUTTON;
		if (button < 0)
			button = button + NUM_BUTTON;
		selectedButton(button);
	}
	else if (ih->isKeyDown(SDL_SCANCODE_D)) {
		button = (button + 1) % NUM_BUTTON;
		selectedButton(button);
	}
	Scene::handleEvents();
}

void EndOfDayScene::selectedButton(int selected) {
	continueButton->getComponent<ButtonComp>()->setHighlighted(false);
	mainMenuButton->getComponent<ButtonComp>()->setHighlighted(false);
	switch (selected)
	{
	case 0:
		continueButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	case 1:
		mainMenuButton->getComponent<ButtonComp>()->setHighlighted(true);
		break;
	}
}



void EndOfDayScene::initCoopMode(bool server) {
	continueButton->setActives(server);
	mainMenuButton->setActives(server);
	active = server;
}

void EndOfDayScene::quitCoopMode() {
	continueButton->setActives(true);
	mainMenuButton->setActives(true);
	active = false;
}

void EndOfDayScene::receive(const Message& message) {
	if (message.id == Message::msg_CONTINUE) {
		dayM->newDay();
	}
	else if (message.id == Message::msg_TO_MAINMENU) {
		Game::get()->setExitCoop();
		gm->get()->changeScene((gm->get()->getScene(sc_MAINMENU)));
	}
}
