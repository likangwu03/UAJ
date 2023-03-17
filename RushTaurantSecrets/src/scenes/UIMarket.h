#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../objects/Money.h" // cambiar cuando se cambie la clase Money
#include "../gameObjects/BasketMarket.h"

// UI del supermercado
class UIMarket : public Scene
{
private:
	//const string FONT_PATH = "assets/Fonts/8-bit Madness.ttf";
	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";
	const int FONTSIZE = 50, ICONSIZE = 48, ICONX = 20, ICONY = 15;

	Scene* market;
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt;
	Font* font;
	GameObject* moneyText;
	GameObject* timeText;
	Texture* moneyTextTexture;
	Image* moneyTextImage;
	int intMoney;
	InputHandler* ih;
	BasketMarket* basketMarket;
	GameObject* shopMenu;


public:
	// constructora
	UIMarket(Scene* market);
	~UIMarket();
	void showMoneyText();
	void createGameObjects(_ecs::_grp_id grp, _ecs::_hdr_id handler, string textureName,
		Vector position, float width, float height, float rotation);
	void update();
	void handleEvents() override;
	void render();
	virtual Scene* getConnectedScene() { return market; }
};

