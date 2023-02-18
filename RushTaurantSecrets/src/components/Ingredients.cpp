#include "Ingredients.h"

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	if (ingredients.size() == MAX_INGREDIENTS) {
		removeLastIngredient(); //elimina el ultimo ingrediente añadido
	}
	ingredients.push_back(ingr);
	
	dest.x = coord[ingredients.size() - 1].first + ING_DISPX / 2;
	dest.y = coord[ingredients.size() - 1].second;
	coord.push_back({ dest.x, dest.y });
	for (int i = 0; i < coord.size(); ++i) {
		coord[i].first -= 0.5 * ING_DISPX;
		coord[i].second = transform->getPos().getY() - ING_POSY;
	}
}

void Ingredients::removeLastIngredient() {
	ingredients.pop_back();
	
	for (int i = 0; i < coord.size(); ++i) {
		coord[i].first += 0.5 * ING_DISPX;
		coord[i].second = transform->getPos().getY() - ING_POSY;
	}
	coord.pop_back();
	
}

void Ingredients::removeAllIngredients() {
	//no es un for porque, a pesar de saber las vueltas que da, se va reduciendo el tamaño del vector
	int i = ingredients.size(); //i vale 5 (el numero de ingredientes maximo que se puede llevar) o menos si no esta lleno el vector
	while (i != 0) {
		removeLastIngredient();
		--i;
	}
}

void Ingredients::removeWhenExit() {
	removeAllIngredients();
}

void Ingredients::render() {
	
	dest.w = ING_WIDTH;
	dest.h = ING_HEIGTH;
	debug();
	// se pintan todas las texturas que hay en el vector
	int i = 0;
	for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
		_ecs::_ingredients_id ingr = *it;
		texture = &((*sdl).images().at(to_string(ingr)));

		texture->render(coord[i].first, coord[i].second);

		++i;
	}
}

void Ingredients::debug() {
	bool func = false;
	if (ingredients.size() == coord.size()) func = true;

	cout << func;
}
