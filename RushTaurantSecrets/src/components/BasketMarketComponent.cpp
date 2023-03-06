#include "BasketMarketComponent.h"

BasketMarketComponent::BasketMarketComponent(GameObject* parent) : Component(parent, id), totalDifIngr(0) {
	//cartelM = new CartelManager();
	ih = InputHandler::instance();
}

void BasketMarketComponent::buyIngredient() {
	// si hay un cartel iluminado y se pulsa una tecla para comprarlo
	if (cartelM->isSelected() && ih->isKeyDown(SDLK_SPACE)) {
		// provisional, se añade un ingrediente automáticamente
		// modificar para poder elegir la cantidad
		// añadir gasto de dinero
		if (totalDifIngr < MAX_ING) { // si no ha superado el límite de ingredientes a comprar
			_ecs::_ingredients_id ingrToBuy = cartelM->getIngredient();
			auto it = ingredients.find(ingrToBuy);
			if (it != ingredients.end())
				it->second += 1;
			else {
				ingredients.insert({ ingrToBuy,1 });
				totalDifIngr++;
			}
		}
	}
}

void BasketMarketComponent::renderBasket() {
	// renderiza menú de cesta
	renderTexture(10, sdl->height() - 610, BASKET_SIZE, BASKET_SIZE / 2 + 100, "BASKET_LIST");
	// render de ingredientes
	auto it = ingredients.begin();
	int x = 30 + ING_SIZE, y = sdl->height() - 590 + ING_SIZE, col = 1, fil = 1;
	string textDish;
	while (it != ingredients.end()) {
		if (col >= 7) {
			col = 1; fil++;
		}
		textDish = to_string(it->first);
		renderTexture(x * col, y * fil, ING_SIZE, ING_SIZE, textDish);
		col++;
		it++;
	}
}

void BasketMarketComponent::renderTexture(int x, int y, int w, int h, string text) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	Texture* texture = &((*sdl).images().at(text));

	// renderiza la textura
	texture->render(dest);
}