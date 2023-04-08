#include "BasketMarketComponent.h"
#include "../Utilities/checkML.h"

BasketMarketComponent::BasketMarketComponent(GameObject* parent) : Component(parent, id), totalDifIngr(0),
basketSound(&sdl->soundEffects().at("OPEN_BASKET")),
selectNum(&sdl->soundEffects().at("SELECT_NUM")),
quitIng(&sdl->soundEffects().at("QUIT_ING")),
selectSound(&sdl->soundEffects().at("SELECT")),
confirmSound(&sdl->soundEffects().at("ADD_ING"))
{
	selectNum->setVolume(10);
	basketSound->setVolume(50);
	quitIng->setVolume(50);

	//cartelM = new CartelManager();
	ih = InputHandler::instance();

	basketPosY = sdl->height() - 610;
	basketPosX = 10;

	font = new Font(FONT_PATH, 50);
	totalPrize = 0;
	basketON = false;
	menu = &((*sdl).images().at("BASKET_BUY_MENU"));

	chooseHMMode = false;

	money = GameManager::get()->getMoney();

	selectedIngr = ingredients.end();
}

BasketMarketComponent::~BasketMarketComponent() {
	delete font;
}

void BasketMarketComponent::addToBasket(_ecs::_ingredients_id ing, int n, int addPrice) {
	//hacer algo para addPrice................................
	//addPrice es el dinero total según n cantidades del ingrediente ing añadida a la cesta

	auto it = ingredients.find(ing);
	if (totalDifIngr < MAX_ING || it != ingredients.end()) { // si no ha superado el límite de ingredientes a comprar o el ingrediente ya está en la cesta
		if (totalDifIngr < MAX_ING || it->first == ing) {
			if (it != ingredients.end()) {
				it->second += n;
			}
			else {
				Texture* texture = new Texture(sdl->renderer(), to_string(n), *font, build_sdlcolor(0xFFFFFFFF));
				ingredients.insert({ ing, n });
				totalDifIngr++; //num de dif ing
				delete texture;
			}
			totalPrize += addPrice;
			selectedIngr = ingredients.find(ing);
			setTotalPrize();
		}
	}
}

void BasketMarketComponent::renderBasket() {
	// renderiza menú de cesta
	renderTexture(basketPosX, basketPosY, factorX*BASKET_SIZE, factorY*BASKET_SIZE - 100, "BASKET_LIST");
	SDL_Rect dest;

	// render de precio total
	string totalP = to_string(totalPrize);
	totalP += "$";
	Texture* textureTotal = new Texture(sdl->renderer(), totalP, *font, build_sdlcolor(0x504631ff));
	dest.x = BASKET_SIZE - ING_SIZE * 3 + 5;
	dest.y = BASKET_SIZE - ING_SIZE * 2 + 5;
	dest.w = ING_SIZE;
	dest.h = ING_SIZE;
	textureTotal->render(dest);
	delete textureTotal;
	// render de ingredientes
	if (ingredients.size() == 0)return;
	int x = 30 + ING_SIZE, y = sdl->height() - 590 + ING_SIZE, col = 1, fil = 1;
	string textDish;
	auto it = ingredients.begin();
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
		Texture* textureAmountC = new Texture(sdl->renderer(), to_string(it->second), *font, build_sdlcolor(0xffffffff));
		textureAmountC->render(dest);
		delete textureAmountC;

		// render highlight de ingrediente y para añadir o quitar ingredientes de la cesta
		if (selectedIngr != ingredients.end() && selectedIngr->first == it->first) {
			renderTexture(x * col, y * fil, ING_SIZE + 5, ING_SIZE + 5, "INGREDIENT_HIGHLIGHT");
			if (chooseHMMode) {
				menu->render(x * col - ING_SIZE, y * fil + ING_SIZE + 5);
				int cost = _ecs::MarketIngs[it->first - _ecs::FLOUR].price;

				Texture* textureAmount = new Texture(sdl->renderer(), to_string(it->second), *font, build_sdlcolor(0xf3e5c2ff));
				dest.x = x * col + 8;
				dest.y = y * fil + (3 * ING_SIZE) / 2;
				dest.w = ING_SIZE / 2;
				dest.h = ING_SIZE / 2;
				textureAmount->render(dest);
				delete textureAmount;
			}
		}

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

void BasketMarketComponent::selectIngredientInBasket(SDL_KeyCode key) {
	// izquierda
	if (key == SDLK_LEFT) {
		if (selectedIngr != ingredients.begin() && selectedIngr != ingredients.end()) {
			selectedIngr--;
			selectSound->play();
		}
	}
	// derecha
	else if (key == SDLK_RIGHT && selectedIngr != ingredients.end()) {
		auto it = selectedIngr;
		it++;
		if (it != ingredients.end()) {
			selectedIngr++;
			selectSound->play();
		}
	}
}

void BasketMarketComponent::handleEvents() {
	if (basketON) {
		if (!chooseHMMode) {
			if (ih->isKeyDown(SDLK_LEFT)) selectIngredientInBasket(SDLK_LEFT);
			else if (ih->isKeyDown(SDLK_RIGHT)) selectIngredientInBasket(SDLK_RIGHT);
			else if (ih->isKeyDown(SDLK_RETURN) && ingredients.size() > 0) {
				chooseHMMode = true;
				confirmSound->play();
			}
		}
		else { // (chooseHMMode)
			if (ih->isKeyDown(SDLK_LEFT))
				changeAmount(SDLK_LEFT);
			else if (ih->isKeyDown(SDLK_RIGHT))
				changeAmount(SDLK_RIGHT);
			else if (ih->isKeyDown(SDLK_RETURN)) {
				chooseHMMode = false;

				if (selectedIngr->second == 0) {
					cleanEmptyBasket();
					quitIng->play();
				}
				else confirmSound->play();
			}
		}
	}
}

vector<pair<_ecs::_ingredients_id, int>> BasketMarketComponent::getIngredients() {
	vector<pair<_ecs::_ingredients_id, int>> aux;

	for (auto ing : ingredients)
		aux.push_back({ ing.first, ing.second });
	ingredients.clear();
	return aux;
}

void BasketMarketComponent::setBasketON(bool value) {
	basketON = value;
	basketSound->play();
}

bool BasketMarketComponent::getBasketON() {
	return basketON;
}

void BasketMarketComponent::changeAmount(SDL_KeyCode key) {
	if (key == SDLK_LEFT) {
		if (selectedIngr->second > 0) {
			selectedIngr->second--;
			int cost = _ecs::MarketIngs[selectedIngr->first - _ecs::FLOUR].price;
			totalPrize -= cost;
			selectNum->play();
		}
	}
	else if (key == SDLK_RIGHT && selectedIngr->second < 100) {
		selectedIngr->second++;
		int cost = _ecs::MarketIngs[selectedIngr->first - _ecs::FLOUR].price;
		totalPrize += cost;
		selectNum->play();
	}
}

void BasketMarketComponent::setTotalPrize() {
	money->setPrize(totalPrize);
}

void BasketMarketComponent::cleanEmptyBasket() {
	selectedIngr = ingredients.erase(selectedIngr);
	if (selectedIngr == ingredients.end())selectedIngr = ingredients.begin();
	if (ingredients.size() == 0)selectedIngr = ingredients.end();
}