#include "EndOfDayScene.h"
#include "../../Managers/DayManager.h"
#include "../../Structure/GameManager.h"
#include "../../Managers/Reputation.h"
#include "../../Managers/Money.h"
#include "../Menus/MainMenu.h"
#include "BeforeDayStartScene.h"

#include "../../Utilities/checkML.h"


EndOfDayScene::EndOfDayScene() {
	gm = GameManager::instance();
	ih = InputHandler::instance();

	accDay = 0;
	moneyGoal = 0;
	playerReputation = 0;
	playerMoney = 0;

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
	new Transform(reputationObj, { 150,200 }, { 0,0 }, 75, 75);
	reputationIconT = &(sdlutils().images().at("REPUTATION_ICON"));
	new Image(reputationObj, reputationIconT);

	moneyObj = new GameObject(this);
	new Transform(moneyObj, { 150, 300 }, { 0,0 }, 75, 75);
	moneyIconT = &(sdlutils().images().at("MONEY_ICON"));
	new Image(moneyObj, moneyIconT);

	//fuente
	font1 = new Font("assets/Fonts/light_pixel-7.ttf", 30);
	font2 = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	TTF_SetFontOutline(font2->getTTFFont(), 1);

	reputationtext = "YOUR CURRENT REPUTATION IS: " + to_string(playerReputation);
	moneyText = "TODAY YOU EARNED: " + to_string(playerMoney) + "$";
	bankruptText = "GAME OVER. YOU WENT BANKRUPT!";
	gameOverText = "GAME OVER. CONGRATULATIONS, ALL THE CITY HATES YOU AND YOUR RESTAURANT.";
	//continueText = ""
	//progressedSavedText = 

	//texturas que cambian cada dia
	reputationTexture = new Texture(sdlutils().renderer(), reputationtext, *font1, build_sdlcolor(0x000000FF));
	reputationOutline = new Texture(sdlutils().renderer(), reputationtext, *font2, build_sdlcolor(0xFFFFFFFF));

	moneyTexture = new Texture(sdlutils().renderer(), moneyText, *font1, build_sdlcolor(0x000000FF));
	moneyOutline = new Texture(sdlutils().renderer(), moneyText, *font2, build_sdlcolor(0xFFFFFFFF));

	//texturas que se mantienen iguales
	bankruptTexture = new Texture(sdlutils().renderer(), bankruptText, *font1, build_sdlcolor(0x000000FF));
	gameOverTexture = new Texture(sdlutils().renderer(), gameOverText, *font1, build_sdlcolor(0x000000FF));

	bankruptOutline = new Texture(sdlutils().renderer(), bankruptText, *font2, build_sdlcolor(0xFFFFFFFF));
	gameOverOutline = new Texture(sdlutils().renderer(), gameOverText, *font2, build_sdlcolor(0xFFFFFFFF));

	//botones
	continueButton = new ButtonGO(this, "CONTINUE_BUTTON", "BUTTON2_HIGHLIGHT", Vector(BUTTON1_X, BUTTON1_Y), BUTTON_W, BUTTON_H, 
		[&]() {
			dayM->newDay();
		});
	continueButton->setAlive(false);
	continueButton->getComponent<ButtonComp>()->setHighlighted(true);

	mainMenuButton = new ButtonGO(this, "MAINM_BUTTON_UP", "BUTTON2_HIGHLIGHT", Vector(BUTTON2_X, BUTTON2_Y), BUTTON_W, BUTTON_H, 
		[&]() {
		   gm->get()->changeScene((gm->get()->getMainMenu()));
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
	delete gameOverTexture;
	delete reputationOutline;
	delete moneyOutline;
	delete bankruptOutline;
	delete gameOverOutline;
}

void EndOfDayScene::reset() {
	accDay = dayM->getDay();
	moneyGoal = dayM->getDailyObjective();
	playerReputation = gm->getReputation()->getReputation();
	playerMoney = gm->getMoney()->getEarnedMoney();

	//gameOver();
	_gameOver = false; //PARA PRUEBAS SOLAMENTE

	reputationtext = "YOUR CURRENT REPUTATION IS: " + to_string(playerReputation);
	moneyText = "TODAY YOU EARNED: " + to_string(playerMoney) + "$ OUT OF " + to_string(moneyGoal) + "$";
	
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

	reputationTexture->render({250, 225, reputationTexture->width(), reputationTexture->height()});
	moneyTexture->render({250, 325, moneyTexture->width(), moneyTexture->height()});

	reputationOutline->render({ 250, 225, reputationTexture->width(), reputationTexture->height() });
	moneyOutline->render({ 250, 325, moneyTexture->width(), moneyTexture->height() });

	if (!_gameOver) { //el juego no se ha perdido
		continueButton->setAlive(true);
		mainMenuButton->setAlive(true);
	}
	else { //el juego se ha perdido
		if ((playerMoney < moneyGoal || playerMoney <= 0) && playerReputation <= 0)
		{
			bankruptTexture->render({50, 450, bankruptTexture->width(), bankruptTexture->height()});
			bankruptOutline->render({ 50, 450, bankruptTexture->width(), bankruptTexture->height() });

			gameOverTexture->render({50, 550, gameOverTexture->width(), gameOverTexture->height()});
			gameOverOutline->render({ 50, 550, gameOverTexture->width(), gameOverTexture->height() });
			
		}
		else if (playerMoney < moneyGoal || playerMoney <= 0) {
			bankruptTexture->render({ 200, 450, bankruptTexture->width(), bankruptTexture->height() });
			bankruptOutline->render({ 200, 450, bankruptTexture->width(), bankruptTexture->height() });
		}
		else if (playerReputation <= 0) {
			gameOverTexture->render({ 50, 450, gameOverTexture->width(), gameOverTexture->height() });
			gameOverOutline->render({ 50, 450, gameOverTexture->width(), gameOverTexture->height() });
		}

		gameOver();
	}


}

void EndOfDayScene::gameOver() {
	if (playerReputation <= 0 || playerMoney < moneyGoal) _gameOver = true; 
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