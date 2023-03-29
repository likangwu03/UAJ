#pragma once
#include "../Structure/Scene.h"
#include "../Managers/DayManager.h"


class Image;
class DayManager;

class EndOfDayScene : public Scene {
private:
	GameObject* reputationObj;
	GameObject* gameOverObj;
	GameObject* backgroundObj;

	Texture* backgroundT;
	Texture* gameOverT;
	Texture* reputationT;
	
	Font* font1;
	Font* font2;

	DayManager* dayM;

	GameManager* gm;
	InputHandler* ih;

	string reputationtext;
	string moneyText;
	string bankruptText;
	string gameOverText;
	string continueText;

	int accDay;
	int moneyGoal;
	int playerReputation;
	int playerMoney;

	bool gameOver;

	void toMainMenu();
	void toNextDay();

public:
	EndOfDayScene();
	~EndOfDayScene();
	void reset();
	virtual void render();
	virtual void handleEvents();
	


};
