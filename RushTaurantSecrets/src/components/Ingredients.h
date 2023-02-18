#pragma once
#include "../structure/Food_def.h"
#include "../structure/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"

using namespace std;
using namespace _ecs;

// no hace falta inicializar el vector (se puede borrar)
const int NUM_INGREDIENTS_IN_INVENTARY = 4;

class Ingredients: public Component {
	const float ING_HEIGTH = 50;
	const float ING_WIDTH = 50;
	const float ING_POSX = 50;
	//constante que parametriza a qu� altura sobre el jugador se sit�an los ingredientes
	const float ING_POSY = 30;
	//constante que deja un espacio entre ingredientes
	const float ING_DISPX = 20;

private:
	const int MAX_INGREDIENTS = 4;
	// vector de ingredientes
	vector<_ecs::_ingredients_id> ingredients = { QUESO,HARINA,HUEVO }; //para demo, luego se borra; 
	Texture* texture;
	Transform* transform;
	SDLUtils* sdl;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INGREDIENTS;
	Ingredients(GameObject* parent) :Component(parent, id), sdl(SDLUtils::instance()), texture(nullptr) {
		transform = parent->getComponent<Transform>();
	}
	//devuelve por ref
	vector<_ecs::_ingredients_id>& getIngredients() { return ingredients; };
	void addIngredient(_ecs::_ingredients_id ingr);
	void removeLastIngredient();
	void removeAllIngredients();
	void removeWhenExit();
	void render();

};