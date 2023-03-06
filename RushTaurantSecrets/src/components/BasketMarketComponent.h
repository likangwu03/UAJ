#pragma once
#include "../structure/Component.h"
#include <unordered_map>
#include "../structure/Food_def.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../structure/CollisionsManager.h"
#include "../structure/CartelManager.h"

using namespace std;

class BasketMarketComponent : public Component
{
private:
	const int BASKET_SIZE = 600;
	const int ING_SIZE = 50;
	const int MAX_ING = 12;

	// lista de ingredientes en la cesta y su cantidad
	unordered_map<_ecs::_ingredients_id, int> ingredients;
	SDLUtils* sdl = SDLUtils::instance();
	InputHandler* ih;
	CartelManager* cartelM = CartelManager::instance();
	int totalDifIngr;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SM_INVENTORY;
	BasketMarketComponent(GameObject* parent);
	void buyIngredient();
	void renderBasket();
	void renderTexture(int x, int y, int w, int h, string text);
};