#include "BasketMarketComponent.h"

BasketMarketComponent::BasketMarketComponent(GameObject* parent) : Component(parent, id) {

}

void BasketMarketComponent::buyIngredient() {

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