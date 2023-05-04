#pragma once
#include "../Definitions/Food_def.h"
#include "../Structure/Component.h"
#include "../Utilities/SDLUtils.h"
#include "../Structure/GameObject.h"
#include "Transform.h"
#include "../Structure/Scene.h"
#include "KitchenIslandComp.h"
#include "../Utilities/InputHandler.h"
#include <vector>
#include <utility>
#include "../Components/ShowControlComp.h"

using namespace std;
using namespace _ecs;

class KitchenIslandComp;
class Ingredients: public Component {
	const int BUBBLE_X = 780, BUBBLE_Y = 10, BUBBLE_W = 252, BUBBLE_H = 65;
	const float ING_SIZE = 30, ING_Y = 33, ING_OFFSET = 48, ING_CENTER = 19;
	const pair<float,float> STARTING_COORDS = { BUBBLE_X + BUBBLE_W / 2 - ING_CENTER, ING_Y };


private:
	const int MAX_INGREDIENTS = 5;
	// vector de ingredientes
	vector<_ecs::_ingredients_id> ingredients;
	Texture* bubble_tex;
	Texture* return_icon;
	Texture* clean_icon;
	SDLUtils* sdl;
	//vector de coordenadas de ingredientes para renderizarlos
	vector<pair<float, float>> coord;
	// rectángulo en el mundo donde se va a colocar la textura
	SDL_Rect dest;
	SDL_Rect dest_bubble;	
	KitchenIslandComp* kitchenIsland; //para devolver ing a la mesa
	SoundEffect* pickIng;
	SoundEffect* returnIng;
	ShowControlComp* showControl;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INGREDIENTS;
	Ingredients(GameObject* parent);
	
	void setKitchenIsland(KitchenIslandComp* k) { kitchenIsland = k; }
	//devuelve por ref
	vector<_ecs::_ingredients_id>& getIngredients() { return ingredients; };
	bool addIngredient(_ecs::_ingredients_id ingr);
	void removeLastIngredient();
	void removeAllIngredients();
	void cookingIngredients();
	void render();
	void nextDay()override;
	void initComponent()override;
};