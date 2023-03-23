#pragma once
#include "../Structure/Scene.h"
#include "../Utilities/SDLUtils.h"
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Managers/Money.h" // cambiar cuando se cambie la clase Money
#include "../GameObjects/BasketMarket.h"
#include "../GameObjects/ButtonGO.h"
#include "../GameObjects/DailyMenu.h"

// UI del supermercado
class UIMarket : public Scene
{
private:
	const string FONT_PATH = "assets/Fonts/EpilepsySansBold.ttf";
	const float FONTSIZE = 50, ICONSIZE = 48, ICONX = 20, ICONY = 15, CENTEROUTLINE = 4;

	Scene* market;
	SDLUtils* sdl = SDLUtils::instance();
	Font* font;
	Font* outline;

	Money* moneyTxt;
	Texture* moneyTexture;
	Texture* moneyOutline;
	SDL_Rect moneyRect;
	SDL_Rect moneyOutlineRect;
	int intMoney;

	InputHandler* ih;
	BasketMarket* basketMarket;
	GameObject* shopMenu;
	DailyMenu* menu;
	bool menuToggled;

	void toggleDailyMenu();


public:
	// constructora
	UIMarket(Scene* market);
	~UIMarket();
	void showMoneyText();
	void createGameObjects(_ecs::_grp_id grp, string textureName, Vector position,
		float width, float height, float rotation, _ecs::_hdr_id handler = _ecs::hdr_INVALID);
	void update();
	void handleEvents() override;
	void render();
	void setDailyMenu();
	virtual Scene* getConnectedScene() { return market; }
};

