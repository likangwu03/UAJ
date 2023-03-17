#include "BasketMarketComponent.h"
#include "../utils/checkML.h"

BasketMarketComponent::BasketMarketComponent(GameObject* parent) : Component(parent, id), totalDifIngr(0) {
	//cartelM = new CartelManager();
	ih = InputHandler::instance();

	basketPosY = sdl->height() - 610;
	basketPosX = 10;

	font = new Font(FONT_PATH, 50);
	totalPrize = 0;
}

BasketMarketComponent::~BasketMarketComponent() {
	delete font;
}

void BasketMarketComponent::addToBasket(_ecs::_ingredients_id ing, int n,int addPrice) {
	//hacer algo para addPrice................................
	//addPrice es el dinero total según n cantidades del ingrediente ing añadida a la cesta

	auto it = ingredients.find(ing);
	if (totalDifIngr < MAX_ING || it->first == ing) { // si no ha superado el límite de ingredientes a comprar o el ingrediente ya está en la cesta

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
		totalPrize += addPrice;
	}
}

void BasketMarketComponent::renderBasket() {
	// renderiza men?de cesta
	renderTexture(basketPosX, basketPosY, BASKET_SIZE, BASKET_SIZE - 100, "BASKET_LIST");
	// render de ingredientes
	auto it = ingredients.begin();
	int x = 30 + ING_SIZE, y = sdl->height() - 590 + ING_SIZE, col = 1, fil = 1;
	string textDish;
	SDL_Rect dest;
	while (it != ingredients.end()) {
		if (col >= 7) {
			col = 1; fil++;
		}
		textDish = to_string(it->first);
		renderTexture(x * col, y * fil, ING_SIZE, ING_SIZE, textDish);
		// renderizar número
		dest.x = x * col + 2 * ING_SIZE / 3;
		dest.y = y * fil + ING_SIZE / 2 + 3;
		dest.w = ING_SIZE / 3;
		dest.h = ING_SIZE / 3;
		renderTexture(x * col + ING_SIZE / 2, y * fil + ING_SIZE / 2, ING_SIZE / 2, ING_SIZE / 2, "KI_ICON");
		it->second.text->render(dest);

		col++;
		it++;
	}
	// render de precio total
	Texture* textureTotal = new Texture(sdl->renderer(), to_string(totalPrize), *font, build_sdlcolor(0x000000FF));
	dest.x = BASKET_SIZE - ING_SIZE * 3 + 5;
	dest.y = BASKET_SIZE - ING_SIZE * 2 + 5;
	dest.w = ING_SIZE;
	dest.h = ING_SIZE;
	textureTotal->render(dest);
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