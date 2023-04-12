#include "EndOfDayScene.h"
#include "../Managers/DayManager.h"
#include "../Structure/GameManager.h"
#include "../Managers/Reputation.h"
#include "../Managers/Money.h"
#include "../Scenes/MainMenu.h"
#include "../Scenes/BeforeDayStartScene.h"

#include "../Utilities/checkML.h"


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
	backgroundT = new Texture(sdlutils().renderer(), "assets/options_bg.png");
	new Image(backgroundObj, backgroundT);

	//icono reputación
	reputationObj = new GameObject(this);
	new Transform(reputationObj, { 150,200 }, { 0,0 }, 75, 75);
	reputationIconT = new Texture(sdlutils().renderer(), "assets/sprites/UI/HUD/reputation_icon.png");
	new Image(reputationObj, reputationIconT);

	moneyObj = new GameObject(this);
	new Transform(moneyObj, { 150, 300 }, { 0,0 }, 75, 75);
	moneyIconT = new Texture(sdlutils().renderer(), "assets/sprites/UI/HUD/money_icon.png");
	new Image(moneyObj, moneyIconT);

	//fuente
	font1 = new Font("assets/Fonts/light_pixel-7.ttf", 30);
	//font2 = new Font("assets / Fonts / light_pixel-7.ttf", 50);

	reputationtext = "YOUR CURRENT REPUTATION IS: " + to_string(playerReputation);
	moneyText = "TODAY YOU EARNED: " + to_string(playerMoney) + "$";
	bankruptText = "GAME OVER. YOU WENT BANKRUPT!";
	gameOverText = "GAME OVER. CONGRATULATIONS, ALL THE CITY HATES YOU AND YOUR RESTAURANT.";
	//continueText = ""
	//progressedSavedText = 

	//texturas que cambian cada dia
	reputationTexture = new Texture(sdlutils().renderer(), reputationtext, *font1, build_sdlcolor(0x000000FF));
	moneyTexture = new Texture(sdlutils().renderer(), moneyText, *font1, build_sdlcolor(0x000000FF));

	//texturas que se mantienen iguales
	bankruptTexture = new Texture(sdlutils().renderer(), bankruptText, *font1, build_sdlcolor(0x000000FF));
	gameOverTexture = new Texture(sdlutils().renderer(), gameOverText, *font1, build_sdlcolor(0x000000FF));
}

EndOfDayScene::~EndOfDayScene() {

	delete backgroundT;
	delete reputationIconT;
	delete moneyIconT;
	delete font1;
	//delete font2;
	delete reputationTexture;
	delete moneyTexture;
	delete bankruptTexture;
	delete gameOverTexture;
}

void EndOfDayScene::reset() {
	accDay = dayM->getDay();
	moneyGoal = dayM->getDailyObjective();
	playerReputation = gm->getReputation()->getReputation();
	playerMoney = gm->getMoney()->getMoney();

	gameOver();

	reputationtext = "YOUR CURRENT REPUTATION IS: " + to_string(playerReputation);
	moneyText = "TODAY YOU EARNED: " + to_string(playerMoney) + "$ OUT OF " + to_string(moneyGoal) + "$";
	
	delete reputationTexture;
	delete moneyTexture;

	reputationTexture = new Texture(sdlutils().renderer(), reputationtext, *font1, build_sdlcolor(0x000000FF));
	moneyTexture = new Texture(sdlutils().renderer(), moneyText, *font1, build_sdlcolor(0x000000FF));
}

void EndOfDayScene::render() {
	Scene::render();

	reputationTexture->render({250, 225, reputationTexture->width(), reputationTexture->height()});
	moneyTexture->render({250, 325, moneyTexture->width(), moneyTexture->height()});

	if (!_gameOver) { //el juego no se ha perdido

	}
	else { //el juego se ha perdido
		if (playerMoney < moneyGoal && playerReputation <= 0)
		{
			bankruptTexture->render({50, 450, bankruptTexture->width(), bankruptTexture->height()});
			gameOverTexture->render({50, 550, gameOverTexture->width(), gameOverTexture->height()});
			
		}
		else if (playerMoney < moneyGoal) bankruptTexture->render({50, 450, bankruptTexture->width(), bankruptTexture->height() });
		else if (playerReputation <= 0) gameOverTexture->render({50, 450, gameOverTexture->width(), gameOverTexture->height() });

		gameOver();
	}


}

void EndOfDayScene::gameOver() {
	if (playerReputation <= 0 || playerMoney < moneyGoal) _gameOver = true;
}


void EndOfDayScene::toMainMenu() {
	gm->get()->changeScene((gm->get()->getMainMenu()));
}


//void EndOfDayScene::toNextDay() {
//	dayM->nextDay();
//	GameManager::get()->getBeforeDayStart()->reset();
//	GameManager::get()->changeScene(GameManager::get()->getBeforeDayStart());
//	dayM->getSound()->play();
//}


void EndOfDayScene::handleEvents() {
	//aqui toMainMenu

	//aqui toNextDay-> no se puede hacer si se pierde la partida
	if ((ih->joysticksInitialised() && ih->getButtonState(0, SDL_JOYBUTTONDOWN)) || ih->keyDownEvent()) {
		dayM->newDay();
	}
}