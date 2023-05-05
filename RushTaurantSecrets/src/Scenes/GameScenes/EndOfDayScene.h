#pragma once
#include "../../Structure/Scene.h"
#include "../../Managers/DayManager.h"
#include "../../GameObjects/ButtonGO.h"


class Image;
class DayManager;

class EndOfDayScene : public Scene {
private:

	const int NUM_BUTTON = 2;
	int button;

	//boton continue
	const int BUTTON1_X = 300;
	const int BUTTON1_Y = 500;
	const float BUTTON_W = 96 * 3.2;
	const float BUTTON_H = 32 * 3.2;

	//boton a main menu
	const int BUTTON2_X = 700;
	const int BUTTON2_Y = 500;

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
	Texture* noRepTexture;
	//texturas para textos con outline
	Texture* reputationOutline;
	Texture* moneyOutline;
	Texture* bankruptOutline;
	Texture* noRepOutline;
	
	SDL_Rect bankruptRect;
	SDL_Rect noRepRect;
	
	Font* font1;
	Font* font2;
	Font* font3;
	Font* font4;

	DayManager* dayM;

	GameManager* gm;
	InputHandler* ih;

	ButtonGO* continueButton;
	ButtonGO* mainMenuButton;

	string reputationtext;
	string moneyText;
	string bankruptText;
	string noRepText;
	string continueText;
	string progressSavedtext;

	int accDay;
	int moneyGoal;
	int playerReputation;
	int playerMoney;
	int initPlayerMoney;
	int earnedMoney;

	bool _gameOver;
	void gameOver();

public:
	EndOfDayScene();
	~EndOfDayScene();
	void reset();
	virtual void render();
	virtual void handleEvents();
	
	void selectedButton(int selected);


	void initCoopMode(bool server)override;
	void quitCoopMode() override;

	void receive(const Message& message);
};
