#pragma once
#include "../structure/Food_def.h"
#include "../structure/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <vector>

using namespace _ecs;
using namespace std;

class Transform;
class GameObject;

const int NUM_INGREDIENTS_IN_INVENTARY = 4;

class Ingredients: public Component {
private:
	//lista de ingredientes
	vector<_ingredients_id> ingredients[NUM_INGREDIENTS_IN_INVENTARY];
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INGREDIENTS;
	Texture* texture;
	Transform* transform;
	SDLUtils* sdl;

public:
	Ingredients(GameObject* parent);
	void addIngredient(_ingredients_id ing);
	void removeLastIngredient(_ingredients_id ing);
	void removeAllIngredients();
	void removeWhenExit();
	void render();

};