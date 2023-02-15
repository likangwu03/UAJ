#include "Ingredients.h"

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	ingredients.push_back(ingr);
}

void Ingredients::removeLastIngredient() {
	ingredients.pop_back();
}

void Ingredients::removeAllIngredients() {

}

void Ingredients::removeWhenExit() {

}

void Ingredients::render() {
	// rectángulo en el mundo donde se va a colocar la textura
	SDL_Rect dest;
	dest.x = transform->getPos().getX();
	dest.y = transform->getPos().getY();
	dest.w = transform->getW();
	dest.h = transform->getH();

	// se pintan todas las texturas que hay en el vector
	for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
		_ecs::_ingredients_id ingr = *it;
		texture = &((*sdl).images().at(to_string(ingr)));
		texture->render(dest);
	}
}
