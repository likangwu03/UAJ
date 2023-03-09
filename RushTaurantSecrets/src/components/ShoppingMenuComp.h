#pragma once

#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../components/BasketMarketComponent.h"
class ShoppingMenuComp :public Component
{
private:
	const float
		MENU_WIDTH = 230,
		MENU_HEIGHT = 115,
		PLAYER_OFFSETY = -5,

		PRICE_OFFSETX = 31, //respecto del men¨²
		PRICE_OFFSETY = 9,
		PRICE_WIDTH = 27,
		PRICE_HEIGHT = 27,

		ING_OFFSETX = 17,
		ING_OFFSETY = 45,
		ING_WIDTH = 60,
		ING_HEIGHT = 60,

		NUM_OFFSETX = 110,
		NUM_OFFSETY = 63,
		NUM_WIDTH = 32,
		NUM_HEIGHT = 25,

		TOT_OFFSETX = 116,
		TOT_OFFSETY = 9,
		TOT_WIDTH = 116,
		TOT_HEIGHT = 34;

	int totalPrice;
	int number;
	int price;

	Font* font;
	Texture* menu;
	Texture* priceTex;
	Texture* numberTex;
	Texture* totalPriceTex;
	Texture* ingTex;
	_ecs::_ingredients_id ing;

	Transform* playerTransform;
	BasketMarketComponent* basket;
	SDLUtils* sdl;
	InputHandler* ih;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SHOP_MENU;
	ShoppingMenuComp(GameObject* parent);
	~ShoppingMenuComp();
	virtual void initComponent();
	virtual void handleEvents();
	virtual void render();
	void increaseN();
	void decreaseN();
	void setIngredient();
	void changePrice();
	void openMenu(_ecs::_ingredients_id _id);
	void closeMenu();
};


