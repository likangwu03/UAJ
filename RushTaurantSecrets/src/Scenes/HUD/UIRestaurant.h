#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/SDLUtils.h"
#include "../../GameObjects/Inventory.h"
#include "../../GameObjects/Clock.h"
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
	const string FONT_PATH = "assets/Fonts/chary___.ttf";
	const float FONTSIZE = 50, ICONSIZE = 48, ICONX = 20, ICONY = 15, CENTEROUTLINE = 4;
	const int REP0 = 0, REP1 = 0, REP2 = 20, REP3 = 40, REP4 = 60, REP5 = 80;

	SDLUtils* sdl = SDLUtils::instance();
	Font* font;
	Font* outline;
	Font* font1;
	Font* outline1;
	
	Reputation* reputation;
	int actReputation;
	array<bool, 5> stars;
	Texture* fullStarTexture;

	Money* moneyTxt;
	Texture* moneyTexture;
	Texture* moneyOutline;
	SDL_Rect moneyRect;
	SDL_Rect moneyOutlineRect;


	int startingMoney, currentMoney, intObjective, moneyDiff;
	Texture* objectiveTexture;
	Texture* objectiveOutline;
	SDL_Rect objectiveRect;
	SDL_Rect objectiveOutlineRect;

	Inventory* inventory;

	Clock* clock;

	float lastTime;
	DailyMenu* menu;
	bool menuToggled;

	int accDay;
	Texture* dayTexture;
	Texture* dayOutline;
	string dayText;

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
	void showMoneyText();
	void renderStar(int x, int y);
	void reputationManager();
	void checkStarsArray();
	void checkRenderStar();
	void setDailyMenu();
	Clock* getClock() const { return clock; }

	void update();
	void render();
	void reset();
	void nextDay();
};