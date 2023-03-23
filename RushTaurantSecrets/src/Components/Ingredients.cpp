#include "../Utilities/checkML.h"
#include "Ingredients.h"


Ingredients::Ingredients(GameObject* parent) : Component(parent, id), sdl(SDLUtils::instance()), texture(nullptr) {
	coord = { STARTING_COORDS };
	dest_bubble = { BUBBLE_X, BUBBLE_Y, BUBBLE_W, BUBBLE_H };
	dest.w = dest.h = ING_SIZE;
}

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	// si el iterador llega al final, es que el iterador no está
	if (std::find(ingredients.begin(), ingredients.end(), ingr) == ingredients.end()) {
		if (ingredients.size() == MAX_INGREDIENTS) {
			removeLastIngredient(); //elimina el ultimo ingrediente añadido
		}
		ingredients.push_back(ingr);

		if (!ingredients.empty()) {
			int i = 0;
			for (i = 0; i < coord.size(); ++i) {
				coord[i].first -= ING_OFFSET / 2;
			}
			//Nuevas coordenadas del nuevo ingrediente
			coord.push_back( {coord[i - 1].first, ING_Y} );
			coord[i].first += ING_OFFSET;
		}
	}
}

void Ingredients::removeLastIngredient() {
	if (!ingredients.empty()) {
 		kitchenIsland->returnIngredient(ingredients[ingredients.size() - 1]);
		ingredients.pop_back();

		for (int i = 0; i < coord.size(); ++i) {
			coord[i].first += ING_OFFSET / 2;
		}
		coord.pop_back();
	}
}

void Ingredients::removeAllIngredients() {
	while (!ingredients.empty()) {
		//devolver a la mesa
		removeLastIngredient();
	}
	coord = { STARTING_COORDS };

}

void Ingredients::cookingIngredients() {
	int i = ingredients.size(); 
	while (i != 0) {
		ingredients.pop_back();

		for (auto& coords : coord) {
			coords.first += (0.5 * ING_OFFSET);
		}
		coord.pop_back();
		--i;
	}
	coord = { STARTING_COORDS };
}

void Ingredients::removeWhenExit() {
	//el método actual solo se llama cuando el personaje sale de la cocina
	removeAllIngredients();	
}

void Ingredients::render() {
	if (!ingredients.empty()) {
		bubble_tex = &((*sdl).images().at("BUBBLE"));
		bubble_tex->renderFrame(dest_bubble, 0, ingredients.size() - 1, 0);
	}
	
	int k = 0; // mejor con un iterador.
	for (auto& ingredient : ingredients) {
		_ecs::_ingredients_id ingr = ingredient;
		texture = &((*sdl).images().at(to_string(ingr)));
		dest.x = coord[k].first;
		dest.y = ING_Y;
		texture->render(dest);
		++k;
	}
	
}
