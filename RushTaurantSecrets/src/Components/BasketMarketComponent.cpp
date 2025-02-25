﻿#include "BasketMarketComponent.h"
#include "../Utilities/checkML.h"
#include "../Structure/Game.h"
#include "../Utilities/CoopHandler.h"

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

	ih = InputHandler::instance();

	basketPosY = sdl->height() - 610;
	basketPosX = 10;

	font = new Font(FONT_PATH, 50);
	totalPrice = 0;
	basketON = false;
	menu = &((*sdl).images().at("BASKET_BUY_MENU"));

	chooseHMMode = false;

	money = GameManager::get()->getMoney();

	selectedIngr = ingredients.end();
	isOnRegister = false;
}

BasketMarketComponent::~BasketMarketComponent() {
	delete font;
}
void BasketMarketComponent::initComponent() {
	showControl = new ShowControlComp(parent, {
		{ControlsType::key_LEFT,ControlsType::play_LS,ControlsType::xbox_LS,Vector(5,0),40,40} ,
		{ControlsType::key_RIGHT,ControlsType::play_RS,ControlsType::xbox_RS,Vector(90,0),40,40} ,
		{ControlsType::key_ENTER,ControlsType::play_Cross,ControlsType::xbox_A,Vector(45, -65),35,35} });
	showControl->initComponent();

}
void BasketMarketComponent::addToBasket(_ecs::_ingredients_id ing, int n, int addPrice) {
	//addPrice es el dinero total según n cantidades del ingrediente ing añadida a la cesta

	auto it = ingredients.find(ing);
	if ((totalDifIngr < MAX_ING || it != ingredients.end()) && n > 0) { // si no ha superado el límite de ingredientes a comprar o el ingrediente ya está en la cesta
		if (totalDifIngr < MAX_ING || it->first == ing) {
			if (it != ingredients.end()) {
				it->second += n;
			}
			else {
				//Texture* texture = new Texture(sdl->renderer(), to_string(n), *font, build_sdlcolor(0xFFFFFFFF));
				it = ingredients.insert({ ing, n }).first;
				totalDifIngr++; //num de dif ing
				//delete texture;
			}
			totalPrice += addPrice;
			selectedIngr = ingredients.find(ing);
			setTotalPrice();
			Message m;
			m.id = Message::msg_BASKET;
			m.basket.ing = ing; m.basket.n = it->second;
			Game::get()->getCoopHandler()->send(m);
		}
	}
}

void BasketMarketComponent::renderBasket() {
	// renderiza menú de cesta
	renderTexture(basketPosX, basketPosY, BASKET_SIZE, BASKET_SIZE - 100, "BASKET_LIST");
	SDL_Rect dest;

	// render de precio total
	string totalP = to_string(totalPrice);
	totalP += "$";
	Texture* textureTotal = new Texture(sdl->renderer(), totalP, *font, build_sdlcolor(0x504631ff));
	dest.x = basketPosX + ING_SIZE * 1.75;
	dest.y = BASKET_SIZE - ING_SIZE * 1.75;
	dest.w = textureTotal->width();
	dest.h = textureTotal->height();
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
		dest.x = x * col + 2 * ING_SIZE / 3 - ING_AMT_OFFSET_X;
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
				dest.x = x * col;
				dest.y = y * fil + (3 * ING_SIZE) / 2;
				dest.w = textureAmount->width() / 1.5;
				dest.h = textureAmount->height() / 1.5;
				if (it->second < 10) dest.x += textureAmount->width() / 3;
				textureAmount->render(dest);
				delete textureAmount;
				showControl->render({ (float)(x * col - ING_SIZE + 25),(float)(y * fil + ING_SIZE + 80) });
			}
			else {
				showControl->render({ (float)(x * col - ING_SIZE + 30),(float)(y * fil + ING_SIZE - 10) });
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
			selectSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
			selectSound->play();
		}
	}
	// derecha
	else if (key == SDLK_RIGHT && selectedIngr != ingredients.end()) {
		auto it = selectedIngr;
		it++;
		if (it != ingredients.end()) {
			selectedIngr++;
			selectSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
			selectSound->play();
		}
	}
}

void BasketMarketComponent::handleEvents() {

	if (GameManager::get()->testEnd)return;

	if (basketON) {
		if (!chooseHMMode) {
			if (ih->joysticksInitialised()) {
				if (ih->getXBox()) {
					if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_BACK)) selectIngredientInBasket(SDLK_LEFT);
					else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_GUIDE))selectIngredientInBasket(SDLK_RIGHT);
				}
				else
					if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) selectIngredientInBasket(SDLK_LEFT);
					else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))selectIngredientInBasket(SDLK_RIGHT);
				
				if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A) && ingredients.size() > 0) {
					chooseHMMode = true;
					showControl->changeOffset(Vector(165, -5), 2);
					confirmSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
					confirmSound->play();
				}
			}
			else {
				if (ih->isKeyDown(SDLK_LEFT)) selectIngredientInBasket(SDLK_LEFT);
				else if (ih->isKeyDown(SDLK_RIGHT)) selectIngredientInBasket(SDLK_RIGHT);
				else if (ih->isKeyDown(SDLK_RETURN) && ingredients.size() > 0) {
					chooseHMMode = true;

					showControl->changeOffset(Vector(165, -5), 2);
					confirmSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
					confirmSound->play();
				}

			}
		}

		else { // (chooseHMMode)
			if (ih->joysticksInitialised()) {
				if (ih->getXBox()) {
					if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_BACK)) changeAmount(SDLK_LEFT);
					else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_GUIDE)) changeAmount(SDLK_RIGHT);
				}
				else
					if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) changeAmount(SDLK_LEFT);
					else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) changeAmount(SDLK_RIGHT);

				if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
					chooseHMMode = false;

					showControl->changeOffset(Vector(45, -65), 2);
					Message m;
					m.id = Message::msg_BASKET;
					m.basket.ing = selectedIngr->first;
					m.basket.n = selectedIngr->second;
					Game::get()->getCoopHandler()->send(m);

					if (selectedIngr->second == 0) {
						cleanEmptyBasket();
						quitIng->setVolume(GameManager::instance()->getSoundEffectsVolume());
						quitIng->play();
					}
					else {
						confirmSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
						confirmSound->play();
					}
				}
			}
			else {
				if (ih->isKeyDown(SDLK_LEFT)) changeAmount(SDLK_LEFT);
				else if (ih->isKeyDown(SDLK_RIGHT)) changeAmount(SDLK_RIGHT);
				else if (ih->isKeyDown(SDLK_RETURN)) {
					chooseHMMode = false;
					showControl->changeOffset(Vector(45, -65), 2);

					Message m;
					m.id = Message::msg_BASKET;
					m.basket.ing = selectedIngr->first;
					m.basket.n = selectedIngr->second;
					Game::get()->getCoopHandler()->send(m);

					if (selectedIngr->second == 0) {
						cleanEmptyBasket();
						quitIng->setVolume(GameManager::instance()->getSoundEffectsVolume());
						quitIng->play();
					}
					else {
						confirmSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
						confirmSound->play();
					}
				}



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

vector<pair<_ecs::_ingredients_id, int>> BasketMarketComponent::getTestIngredients()
{
	vector<pair<_ecs::_ingredients_id, int>> aux;
	for (auto ing : ingredients)
		aux.push_back({ ing.first, ing.second });
	return aux;
}

void BasketMarketComponent::enterRegister(bool enter) {
	isOnRegister = enter;
}

void BasketMarketComponent::setBasketON(bool value) {
	if (!isOnRegister) {
		basketON = value;
		basketSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		basketSound->play();
	}
}

bool BasketMarketComponent::getBasketON() {
	return basketON;
}

void BasketMarketComponent::changeAmount(SDL_KeyCode key) {
	if (key == SDLK_LEFT) {
		if (selectedIngr->second > 0) {
			selectedIngr->second--;
			int cost = _ecs::MarketIngs[selectedIngr->first - _ecs::FLOUR].price;
			totalPrice -= cost;
			selectNum->setVolume(GameManager::instance()->getSoundEffectsVolume());
			selectNum->play();
			setTotalPrice();

		}
	}
	else if (key == SDLK_RIGHT && selectedIngr->second < 99) {
		selectedIngr->second++;
		int cost = _ecs::MarketIngs[selectedIngr->first - _ecs::FLOUR].price;
		totalPrice += cost;
		selectNum->setVolume(GameManager::instance()->getSoundEffectsVolume());
		selectNum->play();
		setTotalPrice();

	}
}

void BasketMarketComponent::setTotalPrice() {
	money->setPrice(totalPrice);
}

void BasketMarketComponent::cleanEmptyBasket() {
	selectedIngr = ingredients.erase(selectedIngr);
	if (selectedIngr == ingredients.end())selectedIngr = ingredients.begin();
	if (ingredients.size() == 0)selectedIngr = ingredients.end();
	totalDifIngr--;
}

void BasketMarketComponent::nextDay() {
	totalDifIngr = 0;
	totalPrice = 0;
	basketON = false;
	chooseHMMode = false;
	money = GameManager::get()->getMoney();
	selectedIngr = ingredients.end();
	isOnRegister = false;
}

void BasketMarketComponent::receive(const Message& message) {
	if (message.id == Message::msg_BASKET) {
		auto it = ingredients.find(message.basket.ing);
		if (it != ingredients.end()) {
			totalPrice -= _ecs::MarketIngs[message.basket.ing - FLOUR].price * it->second;
			it->second = message.basket.n;
			if (message.basket.n == 0) {
				if (selectedIngr == it) {
					ingredients.erase(it);
					selectedIngr = ingredients.begin();
				}
				else {
					ingredients.erase(it);
				}
				totalDifIngr--;
			}
		}
		else {
			auto aux = ingredients.insert({ message.basket.ing, message.basket.n });
			totalDifIngr++; //num de dif ing
			if (selectedIngr == ingredients.end()) selectedIngr = aux.first;
		}
		totalPrice += _ecs::MarketIngs[message.basket.ing - FLOUR].price * message.basket.n;
		setTotalPrice();
	}
}