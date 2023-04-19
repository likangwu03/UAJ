#pragma once
#include "../Structure/Component.h"
#include <unordered_map>
#include <map>
#include "../Definitions/Food_def.h"
#include "../Utilities/SDLUtils.h"
#include "Transform.h"
#include "../Managers/CollisionsManager.h"
#include "Image.h"
#include "../Definitions/Food_def.h"
#include "../Managers/Money.h"
#include "../Structure/GameManager.h"

using namespace std;
using namespace _ecs;

class BasketMarketComponent : public Component
{
private:
	const int BASKET_SIZE = 600;
	const int ING_SIZE = 50;
	const int MAX_ING = 11;

	// lista de ingredientes en la cesta y su cantidad
	map<_ecs::_ingredients_id, int> ingredients; // ingredientes y sus cantidades
	map<_ecs::_ingredients_id, int>::iterator selectedIngr;
	//unordered_map<_ecs::_ingredients_id, ingText> ingredients; // ingredientes, sus cantidades y texturas
	//unordered_map<_ecs::_ingredients_id, unordered_map<Texture*, int>::iterator> ingredients; // ingredientes y un iterador a su textura y cantidad
	//unordered_map<Texture*, int> ingTextures; // textura y cantidad de un ingrediente
	SDLUtils* sdl = SDLUtils::instance();
	InputHandler* ih;
	int totalDifIngr;
	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";
	const int OFFSET = 10;
	Font* font;
	int basketPosY;
	int basketPosX;
	int totalPrize;
	bool basketON;
	Texture* menu;
	bool chooseHMMode;

	SoundEffect* basketSound;
	SoundEffect* selectNum;
	SoundEffect* quitIng;
	SoundEffect* selectSound;
	SoundEffect* confirmSound;

	Money* money;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SM_INVENTORY;
	BasketMarketComponent(GameObject* parent);
	~BasketMarketComponent();
	void buyIngredient();
	//llamado por men?de compra
	void addToBasket(_ecs::_ingredients_id ing, int n, int addPrice);
	void renderBasket();
	void renderTexture(int x, int y, int w, int h, string text);
	void selectIngredientInBasket(SDL_KeyCode key);
	void setBasketON(bool value);
	bool getBasketON();
	void changeAmount(SDL_KeyCode key);
	void setTotalPrize();
	void cleanEmptyBasket();

	virtual void handleEvents();
	void receive(const Message& message);
	void addToBasketOnline(_ecs::_ingredients_id ing, int n);

	vector<pair<_ecs::_ingredients_id, int>> getIngredients();
};