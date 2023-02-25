#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include <array>
#include "../gameObjects/Inventory.h"
#include "../objects/Reputation.h"

class GameObject;
class Money;
class Image;
class Inventory;
class Bin;

using namespace std;

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";

	Inventory* inventory;
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt;
	Font* f;
	GameObject* moneyText;
	GameObject* timeText;
	Texture* moneyTextTexture;
	Texture* timeTextTexture;
	Texture* fullStarTexture;
	Image* moneyTextImage;
	Image* timeTextImage;
	int intMoney;
	int time = 0, timeT = 0;
	float lastTime;
	Reputation* reputation = Reputation::instance();
	int actReputation;
	array<bool, 5> stars;

public:
	UIRestaurant();
	~UIRestaurant();

	Inventory* getInventory() { return inventory; };
	Money* getMoney() { return moneyTxt; };
	void showMoneyText();
	void update();
	void showTimeText();
	void checkTime();
	void renderStar(int x, int y);
	void reputationManager();
	void checkStarsArray();
	void checkRenderStar();
};

