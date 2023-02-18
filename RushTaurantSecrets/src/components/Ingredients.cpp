#include "Ingredients.h"

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	ingredients.push_back(ingr);
}

void Ingredients::removeLastIngredient() {
	ingredients.pop_back();
}

void Ingredients::removeAllIngredients() {
	//no es un for porque, a pesar de saber las vueltas que da, se va reduciendo el tamaño del vector
	int i = ingredients.size(); //i vale 5 (el numero de ingredientes maximo que se puede llevar) o menos si no esta lleno el vector
	while (i != 0) {
		ingredients.pop_back();
		--i;
	}
}

void Ingredients::removeWhenExit() {
	removeAllIngredients();
}

void Ingredients::render() {
	// rectángulo en el mundo donde se va a colocar la textura
	SDL_Rect dest;
	dest.x = transform->getPos().getX() + ING_POSX;
	dest.y = transform->getPos().getY() - ING_POSY;
	//dest.w = transform->getW();
	//dest.h = transform->getH();
	dest.w = ING_WIDTH;
	dest.h = ING_HEIGTH;

	// se pintan todas las texturas que hay en el vector
	for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
		_ecs::_ingredients_id ingr = *it;
		texture = &((*sdl).images().at(to_string(ingr)));
		texture->render(dest);
	}
}
