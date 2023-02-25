#pragma once
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../objects/Money.h" // cambiar cuando se cambie la clase Money

// UI del supermercado
class UIMarket : public Scene
{
private:
	SDLUtils* sdl = SDLUtils::instance();
	Money* moneyTxt = new Money();
	Font* f;
	GameObject* moneyText;
	GameObject* timeText;
	Texture* moneyTextTexture;
	Image* moneyTextImage;
	int intMoney;
	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";

public:
	// constructora
	UIMarket();
	void showMoneyText();
	void update();
};

