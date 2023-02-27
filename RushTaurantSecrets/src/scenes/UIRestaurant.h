#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../gameObjects/Inventory.h"
#include <string>
#include <array>

class GameObject;
class Money;
class Image;
class Inventory;
class Bin;
class Reputation;

using namespace std;
using namespace _ecs;

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";

	Inventory* inventory;
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt;
	Font* font;
	GameObject* moneyText;
	GameObject* timeText;
	GameObject* arrow;
	Texture* moneyTextTexture;
	Texture* timeTextTexture;
	Texture* fullStarTexture;
	Image* moneyTextImage;
	Image* timeTextImage;
	int intMoney;
	int time = 0, timeT = 0;
	float lastTime;
	Reputation* reputation;
	int actReputation;
	array<bool, 5> stars;

public:
	UIRestaurant();
	~UIRestaurant();

	Inventory* getInventory() { return inventory; };
	Money* getMoney() { return moneyTxt; };
	void createGameObjects(_ecs::_grp_id grp, _ecs::_hdr_id handler, string textureName,
		Vector position, float width, float height, float rotation);
	void showMoneyText();
	void update();
	void render();
	void showTimeText();
	void checkTime();
	void renderStar(int x, int y);
	void reputationManager();
	void checkStarsArray();
	void checkRenderStar();
	void createEmptyStar(Vector pos);
};

