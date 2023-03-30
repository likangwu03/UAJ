#pragma once
#include "../Structure/Scene.h"
#include "../Managers/DayManager.h"

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
	Font* text;

	string wordDay;
	string press;
	string mnyTarget;

	Texture* background;
	Texture* target;
	Texture* dayTxt;
	Texture* buttonTxt;
	Texture* moneyTarget;
	Texture* bannerTexture;

	int accDay;
	int accGoal;
	
	void toDailyMenu();

public:
	BeforeDayStartScene();
	~BeforeDayStartScene();
	virtual void handleEvents();
	virtual void render();
	virtual void update();
	void init();
	void reset();
};