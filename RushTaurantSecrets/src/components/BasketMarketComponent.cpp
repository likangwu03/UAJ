#include "BasketMarketComponent.h"

BasketMarketComponent::BasketMarketComponent(GameObject* parent) : Component(parent, id) {
	//cartelM = new CartelManager();
	ih = InputHandler::instance();
}

void BasketMarketComponent::buyIngredient() {
	// si hay un cartel iluminado y se pulsa una tecla para comprarlo
	if (cartelM->isSelected() && ih->isKeyDown(SDLK_SPACE)) {
		// provisional, se añade un ingrediente automáticamente
		// modificar para poder elegir la cantidad
		// añadir gasto de dinero
		_ecs::_ingredients_id ingrToBuy = cartelM->getIngredient();
		auto it = ingredients.find(ingrToBuy);
		if (it != ingredients.end())
			it->second++;
		else 
			ingredients.insert({ ingrToBuy,1 });
	}
}

void BasketMarketComponent::renderBasket() {
	// renderiza menú de cesta
	renderTexture(10, sdl->height() - 610, 600, 600, "BASKET_LIST");
	// render de ingredientes
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