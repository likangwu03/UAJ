#include "../Utilities/checkML.h"
#include "Ingredients.h"


Ingredients::Ingredients(GameObject* parent) : Component(parent, id), sdl(SDLUtils::instance()), coord() {
	bubble_tex = &((*sdl).images().at("BUBBLE")); 
	dest_bubble = { BUBBLE_X, BUBBLE_Y, BUBBLE_W, BUBBLE_H };
	dest.w = dest.h = ING_SIZE;
}

bool Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	// si el iterador llega al final, es que el iterador no est�
	if (ingredients.size() < MAX_INGREDIENTS && std::find(ingredients.begin(), ingredients.end(), ingr) == ingredients.end()) {

		ingredients.push_back(ingr);

		if (ingredients.size() == 1)
			coord.push_back(STARTING_COORDS);
		else {
			for (auto& coords : coord) {
				coords.first -= ING_OFFSET / 2;
			}
			//Nuevas coordenadas del nuevo ingrediente
			coord.push_back({ coord.back().first, ING_Y});
			coord.back().first += ING_OFFSET;
		}
		return true;
	}
	else return false;
}

void Ingredients::removeLastIngredient() {
	if (!ingredients.empty()) {
 		kitchenIsland->returnIngredient(ingredients.back());
		ingredients.pop_back();

		for (auto& coords : coord)
			coords.first += ING_OFFSET / 2;

		coord.pop_back();
	}
}

void Ingredients::removeAllIngredients() {
	while (!ingredients.empty()) {
		//devolver a la mesa
		removeLastIngredient();
	}
}

void Ingredients::cookingIngredients() {
	int i = ingredients.size(); 
	while (i != 0) {
		ingredients.pop_back();

		for (auto& coords : coord)
			coords.first += (0.5 * ING_OFFSET);

		coord.pop_back();
		--i;
	}
}


void Ingredients::render() {
	if (!ingredients.empty()) {
		bubble_tex->renderFrame(dest_bubble, 0, ingredients.size() - 1, 0);
	
		int k = 0; // mejor con un iterador.
		for (auto ingredient : ingredients) {
			Texture* texture = &((*sdl).images().at(to_string(ingredient)));
			dest.x = coord[k].first;
			dest.y = ING_Y;
			texture->render(dest);
			++k;
		}
	}
	
}
