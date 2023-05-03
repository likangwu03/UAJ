#pragma once
#include "../../Structure/Scene.h"
#include "../../Managers/DayManager.h"
#include "../../Utilities/SDLUtils.h"
class Image;

class BeforeDayStartScene : public Scene {
	const int OFFSET_DAY = 50;

private:
	DayManager* day;
	GameManager* gm;
	InputHandler* ih;

	GameObject* obj; //objeto para background
	GameObject* targetObj; //objeto para diana
	GameObject* bannerObj; //objeto para el banner

	Font* dayText;
	Font* pressButtonText;
	Font* pressButtonText1;
	Font* text;
	Font* text1;

	string wordDay;
	string press;
	string mnyTarget;

	Texture* background;
	Texture* target;
	Texture* dayTxt;
	Texture* buttonTxt;
	Texture* moneyTarget;
	Texture* bannerTexture;

	SoundEffect* beginSound;

	int accDay;
	int accGoal;
	int initMoney;
	
	void toDailyMenu();

public:
	BeforeDayStartScene();
	~BeforeDayStartScene();
	virtual void handleEvents();
	void render() override;
	//void update() { };
	void init();
	void reset();
	int getInitMoney();

	void initCoopMode(bool server)override;
	void quitCoopMode() override;

	virtual void receive(const Message& message);
};