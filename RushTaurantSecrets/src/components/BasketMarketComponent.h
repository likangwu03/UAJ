#pragma once
#include "../structure/Component.h"
#include <unordered_map>
#include "../structure/Food_def.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../structure/CollisionsManager.h"
#include "../structure/CartelManager.h"
#include "../components/Image.h"

using namespace std;

class BasketMarketComponent : public Component
{
private:
	const int BASKET_SIZE = 600;
	const int ING_SIZE = 50;
	const int MAX_ING = 12;

	struct ingText {
		Texture* text;
		int amount;
	};

	// lista de ingredientes en la cesta y su cantidad
	unordered_map<_ecs::_ingredients_id, ingText> ingredients; // ingredientes, sus cantidades y texturas
	//unordered_map<_ecs::_ingredients_id, unordered_map<Texture*, int>::iterator> ingredients; // ingredientes y un iterador a su textura y cantidad
	//unordered_map<Texture*, int> ingTextures; // textura y cantidad de un ingrediente
	SDLUtils* sdl = SDLUtils::instance();
	InputHandler* ih;
	CartelManager* cartelM = CartelManager::instance();
	int totalDifIngr;
	const string FONT_PATH = "assets/Fonts/Arcadepix Plus.ttf";
	const int OFFSET = 10;
	Font* font;
	Texture* texture;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SM_INVENTORY;
	BasketMarketComponent(GameObject* parent);
	void buyIngredient();
	//llamado por men¨² de compra
	void addToBasket(_ecs::_ingredients_id ing, int n);
	void renderBasket();
	void renderTexture(int x, int y, int w, int h, string text);
};