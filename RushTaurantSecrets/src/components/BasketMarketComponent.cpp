﻿#include "BasketMarketComponent.h"
#include "../utils/checkML.h"

BasketMarketComponent::BasketMarketComponent(GameObject* parent) : Component(parent, id), totalDifIngr(0) {
	//cartelM = new CartelManager();
	ih = InputHandler::instance();

	font = new Font(FONT_PATH, 50);
}

void BasketMarketComponent::addToBasket(_ecs::_ingredients_id ing, int n,int addPrice) {
	//hacer algo para addPrice................................
	//addPrice es el dinero total según n cantidades del ingrediente ing añadida a la cesta

	if (totalDifIngr < MAX_ING) { // si no ha superado el l韒ite de ingredientes a comprar
		auto it = ingredients.find(ing);

		if (it != ingredients.end()) {
			it->second.amount += n;
			Texture* texture = new Texture(sdl->renderer(), to_string(it->second.amount), *font, build_sdlcolor(0xFFFFFFFF));
			it->second.text = texture;
		}
		else {
			Texture* texture = new Texture(sdl->renderer(), to_string(n), *font, build_sdlcolor(0xFFFFFFFF));
			ingredients.insert({ ing, { texture, n} });
			totalDifIngr++; //num de dif ing
		}
	}
}


/*void BasketMarketComponent::buyIngredient() {
	// si hay un cartel iluminado y se pulsa una tecla para comprarlo
	if (cartelM->isSelected() && ih->isKeyDown(SDLK_SPACE)) {
		// provisional, se a馻de un ingrediente autom醫icamente
		// modificar para poder elegir la cantidad
		// a馻dir gasto de dinero
		if (totalDifIngr < MAX_ING) { // si no ha superado el l韒ite de ingredientes a comprar
			_ecs::_ingredients_id ingrToBuy = cartelM->getIngredient();
			auto it = ingredients.find(ingrToBuy);
			if (it != ingredients.end()) {
				it->second.amount += 1;
				Texture* texture = new Texture(sdl->renderer(), to_string(it->second.amount), *font, build_sdlcolor(0xFFFFFFFF));
				it->second.text = texture;
			}
			else {
				Texture* texture = new Texture(sdl->renderer(), to_string(n), *font, build_sdlcolor(0xFFFFFFFF));
				ingredients.insert({ ingrToBuy, { texture, n} });
				totalDifIngr++;
			}
		}
	}
}*/


void BasketMarketComponent::renderBasket() {
	// renderiza men?de cesta
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
		// renderizar n鷐ero
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