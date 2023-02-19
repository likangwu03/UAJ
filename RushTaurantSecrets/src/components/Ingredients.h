#pragma once
#include "../structure/Food_def.h"
#include "../structure/Component.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include <vector>
#include <utility>

using namespace std;
using namespace _ecs;


class Ingredients: public Component {
	const float ING_HEIGTH = 50;
	const float ING_WIDTH = 50;
	//constante que parametriza a qu� altura sobre el jugador se sit�an los ingredientes
	const float ING_POSY = 30;
	//constante que deja un espacio entre ingredientes cuando estos se renderizan
	const float ING_OFFSET = 50;

private:
	const int MAX_INGREDIENTS = 4;
	// vector de ingredientes
	vector<_ecs::_ingredients_id> ingredients;
	Texture* texture;
	Transform* transform;
	SDLUtils* sdl;
	//vector de coordenadas de ingredientes para renderizarlos
	vector<pair<float, float>> coord;
	// rectángulo en el mundo donde se va a colocar la textura
	SDL_Rect dest;

	void debug(); //provisional

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INGREDIENTS;
	Ingredients(GameObject* parent) :Component(parent, id), sdl(SDLUtils::instance()), texture(nullptr) {
		transform = parent->getComponent<Transform>();
		//coord.resize(1);
		coord = { { 0,0 } };
		//para demo, luego se borra; 
		addIngredient(QUESO);
		//addIngredient(HARINA);
		//addIngredient(HUEVO);
	}
	//devuelve por ref
	vector<_ecs::_ingredients_id>& getIngredients() { return ingredients; };
	void addIngredient(_ecs::_ingredients_id ingr);
	void removeLastIngredient();
	void removeAllIngredients();
	void removeWhenExit();
	void render();

};