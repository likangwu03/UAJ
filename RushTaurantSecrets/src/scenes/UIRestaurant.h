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
class Transform;

using namespace std;
using namespace _ecs;

// UI del restaurante 
class UIRestaurant : public Scene
{
private:
	const string FONT_PATH = "assets/Fonts/8-bit Madness.ttf";
	const int REP0 = 0, REP1 = 0, REP2 = 20, REP3 = 40, REP4 = 60, REP5 = 80;
	const int FONTSIZE = 50, ICONSIZE = 48, ICONX = 20, ICONY = 15;
	// parametrizable: 1000 (cada segundo) / 10000 (cada diez segundos)
	const int TIME_CLOCK_REFRESH = 10000, ANGLE = 90, ANGLE_UPDATE = 5;

	Inventory* inventory;
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt;
	Font* font;
	Transform* transform;
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
	int numFullClock; // número de vueltas que ha dado el reloj

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
	void updateClock();
	int getNumFullClock(); // devuelve cuántas vueltas ha dado reloj cuando se llama al método
};

