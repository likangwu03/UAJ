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
	gameOver = false;

	//font1 = new Font();
	//font2 = new Font();

	//reputationtext = 
	//moneyText = 
	//bankruptText = 
	//gameOverText = 
	//continueText =
}

EndOfDayScene::~EndOfDayScene() {

	delete backgroundT;
	delete gameOverT;
	delete reputationT;
	delete font1;
	delete font2;

}

void EndOfDayScene::reset() {
	accDay = dayM->getDay();
	moneyGoal = dayM->getDailyObjective();
	playerReputation = gm->getReputation()->getReputation();
	playerMoney = gm->getMoney()->getMoney();
}

void EndOfDayScene::render() {
	Scene::render();
}


void EndOfDayScene::toMainMenu() {

}


void EndOfDayScene::toNextDay() {
	//dayM->checkDayFinished();
	
}


void EndOfDayScene::handleEvents() {
	//aqui toMainMenu

	//aqui toNextDay
}