#pragma once
#include "../structure/Food_def.h"
#include "../structure/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"

using namespace std;

// no hace falta inicializar el vector (se puede borrar)
const int NUM_INGREDIENTS_IN_INVENTARY = 4;

class Ingredients: public Component {
private:
	// vector de ingredientes
	vector<_ecs::_ingredients_id> ingredients;
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INGREDIENTS;
	Texture* texture;
	Transform* transform;
	SDLUtils* sdl;

public:
	Ingredients(GameObject* parent) :Component(parent, id), sdl(SDLUtils::instance()), texture(nullptr) {
		transform = parent->getComponent<Transform>();
	}

	void addIngredient(_ecs::_ingredients_id ingr);
	void removeLastIngredient();
	void removeAllIngredients();
	void removeWhenExit();
	void render();

};