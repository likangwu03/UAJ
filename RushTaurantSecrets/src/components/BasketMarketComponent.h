#pragma once
#include "../structure/Component.h"
#include <unordered_map>
#include "../structure/Food_def.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

using namespace std;

class BasketMarketComponent : public Component
{
private:
	// lista de ingredientes en la cesta y su cantidad
	unordered_map<_ecs::_ingredients_id, int> ingredients;
	SDLUtils* sdl = SDLUtils::instance();
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SM_INVENTORY;
	BasketMarketComponent(GameObject* parent);
	void buyIngredient();
	void renderBasket();
	void renderTexture(int x, int y, int w, int h, string text);
};

