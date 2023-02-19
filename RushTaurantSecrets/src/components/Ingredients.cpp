#include "Ingredients.h"

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	if (ingredients.size() == MAX_INGREDIENTS) {
		removeLastIngredient(); //elimina el ultimo ingrediente añadido
	}
	ingredients.push_back(ingr);
	
	int i = 0;
	for (i = 0;i < coord.size();++i) {
		coord[i].first -= ING_OFFSET / 2;
		coord[i].second = 0;
	}
	//Nuevas coordenadas del nuevo ingrediente
	coord.push_back({ coord[i-1].first, coord[i-1].second});
	coord[i].first += ING_OFFSET;
	
}

void Ingredients::removeLastIngredient() {
	ingredients.pop_back();
	
	for (int i = 0; i < coord.size(); ++i) {
		coord[i].first += 0.5 * ING_OFFSET;
		coord[i].second = 0;
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
	for (int i = 0; i < coord.size();++i) {
		coord[i].first += transform->getPos().getX();
		coord[i].second += transform->getPos().getY() - ING_POSY;
	}
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
