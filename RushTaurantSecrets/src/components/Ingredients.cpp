#include "Ingredients.h"

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	if (ingredients.size() == NUM_INGREDIENTS_IN_INVENTARY) {
		removeLastIngredient(); //elimina el ultimo ingrediente añadido
		ingredients.push_back(ingr); //en su lugar añade el nuevo ingrediente
	}
	else {
		ingredients.push_back(ingr);
	}
	
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

////Para numero de ingredientes pares
//SDL_Rect Ingredients::createRectEvens() {
//
//}
//
////Para numero de ingredientes impares
//SDL_Rect Ingredients::createRectOdds() {
//	
//}

void Ingredients::render() {
	// rectángulo en el mundo donde se va a colocar la textura
	SDL_Rect dest;
	dest.x = transform->getPos().getX();
	dest.y = transform->getPos().getY() - ING_POSY;
	//dest.w = transform->getW();
	//dest.h = transform->getH();
	dest.w = ING_WIDTH;
	dest.h = ING_HEIGTH;

	// se pintan todas las texturas que hay en el vector
	for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
		_ecs::_ingredients_id ingr = *it;
		texture = &((*sdl).images().at(to_string(ingr)));
		texture->render(dest.x, dest.y);

		if (ingredients.size() > 0) {
			float i = -0.5;
			for (auto it2 = ingredients.begin(); it2 != ingredients.end() - 1; ++it2) {
				texture->render(dest.x - i * ING_DISPX, dest.y);
				i -= -0.5;
			}
		}
		
		
	}

	
}
