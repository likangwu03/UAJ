#pragma once
#include "../../Structure/Scene.h"
#include "../../Managers/DayManager.h"
#include "../../GameObjects/ButtonGO.h"


class Image;
class DayManager;

class EndOfDayScene : public Scene {
private:
	GameObject* reputationObj;
	GameObject* backgroundObj;
	GameObject* moneyObj;

	//textura de objetos
	Texture* backgroundT;
	Texture* reputationIconT;
	Texture* moneyIconT;

	//textura de strings
	Texture* reputationTexture;
	Texture* moneyTexture;
	Texture* bankruptTexture;
	Texture* gameOverTexture;
	
	
	Font* font1;
	Font* font2;

	DayManager* dayM;

	GameManager* gm;
	InputHandler* ih;

	ButtonGO* continueButton;
	ButtonGO* mainMenuButton;

	string reputationtext;
	string moneyText;
	string bankruptText;
	string gameOverText;
	string continueText;
	string progressSavedtext;

	int accDay;
	int moneyGoal;
	int playerReputation;
	int playerMoney;

	bool _gameOver;

	void toMainMenu();
	//void toNextDay();
	void gameOver();

public:
	EndOfDayScene();
	~EndOfDayScene();
	void reset();
	virtual void render();
	virtual void handleEvents();
	
};
