#include "../utils/checkML.h"
#include "Ingredients.h"


void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	// si el iterador llega al final, es que el iterador no está
	if (std::find(ingredients.begin(), ingredients.end(), ingr) == ingredients.end()) {
		if (ingredients.size() == MAX_INGREDIENTS) {
			removeLastIngredient(); //elimina el ultimo ingrediente añadido
		}
		ingredients.push_back(ingr);

		if (ingredients.size() > 0) {
			int i = 0;
			for (i = 0;i < coord.size();++i) {
				coord[i].first -= (0.5 * ING_OFFSET);
				coord[i].second = 0;
			}
			//Nuevas coordenadas del nuevo ingrediente
			coord.push_back({ coord[i - 1].first, coord[i - 1].second });
			coord[i].first += ING_OFFSET;
		}
	}
}

void Ingredients::removeLastIngredient() {
	if (ingredients.size() > 0) {
 		kitchenIsland->returnIngredient(ingredients[ingredients.size() - 1]);
		ingredients.pop_back();

		for (auto& coords : coord) {
			coords.first += (0.5 * ING_OFFSET);
			coords.second = 0;
		}
		coord.pop_back();
	}
}

void Ingredients::removeAllIngredients() {
	//no es un for porque, a pesar de saber las vueltas que da, se va reduciendo el tamaño del vector
	int i = ingredients.size(); //i vale 5 (el numero de ingredientes maximo que se puede llevar) o menos si no esta lleno el vector
	while (i != 0) {
		//devolver a la mesa
		removeLastIngredient();
		--i;
	}
	coord = { { 0,0 } };
	

}

void Ingredients::cookingIngredients() {
	int i = ingredients.size(); 
	while (i != 0) {
		ingredients.pop_back();

		for (auto& coords : coord) {
			coords.first += (0.5 * ING_OFFSET);
			coords.second = 0;
		}
		coord.pop_back();
		--i;
	}
	coord = { { 0,0 } };
}

void Ingredients::removeWhenExit() {
	//el método actual solo se llama cuando el personaje sale de la cocina
	removeAllIngredients();	
}

void Ingredients::render() {
	if (ingredients.size() >= 1) {
		dest_bubble.w = ING_WIDTH * (ingredients.size()) + BUBBLE_OFFSET_X + ING_OFFSET*(ingredients.size()-1)*0.25;
		dest_bubble.h = ING_HEIGHT + 2 * BUBBLE_OFFSET_Y;

		dest.w = ING_WIDTH;
		dest.h = ING_HEIGHT;

		dest_bubble.x = BUBBLE_X - dest_bubble.w / 2;
		dest_bubble.y = BUBBLE_Y;

		bubble_tex = &((*sdl).images().at("BUBBLE"));
		bubble_tex->render(dest_bubble);
	}
	

	//Se añade las coordenadas del jugador sobre las coordenadas centradas en 0,0 para que pasen a estar sobre el player
	for (int i = 0; i < coord.size();++i) {
		coord[i].first += BUBBLE_X;
		coord[i].second += (BUBBLE_Y + BUBBLE_OFFSET_Y / 2);
	}
	// se pintan todas las texturas que hay en el vector

	int k = 0; // mejor con un iterador.
	for (auto& ingredient : ingredients) {
		_ecs::_ingredients_id ingr = ingredient;
		texture = &((*sdl).images().at(to_string(ingr)));
		dest.x = coord[k].first;
		dest.y = coord[k].second;
		texture->render(dest);
		++k;
	}
	
	//Se eliminan las coordenadas del player para que las coordenadas vuelvan a ser sobre 0,0 y no se se haga una suma
	//sobre la anterior en cada tick y que salgan de la pantalla

	for (auto& coords : coord) {
		coords.first -= BUBBLE_X;
		coords.second = 0;
	}
}
