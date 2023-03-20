#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../gameObjects/Inventory.h"
#include "../gameObjects/Clock.h"
#include <string>
#include <array>
#include <vector>

class GameObject;
class Money;
class Image;
class Inventory;
class Bin;
class Reputation;
class Transform;
class DailyMenu;

using namespace std;
using namespace _ecs;

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	const string FONT_PATH = "assets/Fonts/8-bit Madness.ttf";
	const int REP0 = 0, REP1 = 0, REP2 = 20, REP3 = 40, REP4 = 60, REP5 = 80;
	const int FONTSIZE = 50, ICONSIZE = 48, ICONX = 20, ICONY = 15;

	Inventory* inventory;
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt;
	Font* font;
	Transform* transform;
	GameObject* moneyText;
	Texture* moneyTextTexture;
	Texture* fullStarTexture;
	Texture* objectiveTextTexture;
	Image* moneyTextImage;
	Image* timeTextImage;
	Image* objectiveTextImage;
	Transform* objectiveTextTrans;
	int intMoney, intObjective, moneyDiff;
	float lastTime;
	Reputation* reputation;
	int actReputation;
	array<bool, 5> stars;
	DailyMenu* menu;
	bool menuToggled;

	GameObject* dataIcon(Texture* texture, Vector position, float width, float height, float rotation,
		_ecs::_grp_id grp, _ecs::_hdr_id handler);

	GameObject* createIcon(string textureName, Vector position, float width, float height, float rotation = 0,
		_ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID);

	GameObject* createIcon(Texture* texture, Vector position, float width, float height, float rotation = 0,
		_ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID);

	void toggleDailyMenu();

public:
	UIRestaurant();
	~UIRestaurant();

	Inventory* getInventory() const { return inventory; };

	Money* getMoney() const { return moneyTxt; };

	void showMoneyText();

	void renderStar(int x, int y);

	void reputationManager();

	void checkStarsArray();

	void checkRenderStar();

	void setDailyMenu();

	void updateClock();

	void update();

	void render();
};