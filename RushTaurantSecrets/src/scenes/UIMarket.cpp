#include "UIMarket.h"
#include "../structure/GameManager.h"
#include "../objects/Money.h"

#include "../components/ShoppingMenuComp.h"
#include "../utils/checkML.h"

UIMarket::UIMarket(Scene* market) : Scene(),market(market) {
	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = GameManager::instance()->getMoney();
	ih = InputHandler::instance();
	basketMarket = new BasketMarket(this);

	// icono de dinero
	createGameObjects(_ecs::grp_ICONS, "MONEY_ICON", Vector(ICONX, ICONY), ICONSIZE, ICONSIZE, 0);

	// gestión de la cantidad de dinero
	intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);

	font = new Font(FONT_PATH, 50);
	moneyTextTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x000000FF));
	moneyText = new GameObject(this, _ecs::grp_ICONS);
	new Transform(moneyText, Vector(80, ICONY - 3), Vector(0, 0), strMoney.length() * FONTSIZE / 2, FONTSIZE);
	moneyTextImage = new Image(moneyText, moneyTextTexture);

	// icono de men?del día
	createGameObjects(_ecs::grp_ICONS, "DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), 50, 50, 0);

	// icono de cesta
	createGameObjects(_ecs::grp_ICONS, "BASKET_YELLOW", Vector(20, sdl->height() - 90), 68, 70, 0);

	//men¨² de compra
	shopMenu = new GameObject(this, _ecs::grp_GENERAL, hdr_SHOP_MENU1);
	new ShoppingMenuComp(shopMenu);
}

UIMarket::~UIMarket() {
	delete font;
	delete moneyTextTexture;
}


void UIMarket::update() {
	Scene::update();
	showMoneyText();
}

void UIMarket::createGameObjects(_ecs::_grp_id grp, string textureName,
	Vector position, float width, float height, float rotation, _ecs::_hdr_id handler) {
	GameObject* gameObject = new GameObject(this, grp, handler);
	new Transform(gameObject, position, Vector(0, 0), width, height, rotation);
	new Image(gameObject, &((*sdl).images().at(textureName)));
}


void UIMarket::showMoneyText() {
	// si la cantidad de dinero ha variado, lo muestra por pantalla
	if (intMoney != moneyTxt->getMoney()) {
		intMoney = moneyTxt->getMoney();
		std::string strMoney = std::to_string(intMoney);
		delete moneyTextTexture;
		moneyTextTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x000000FF));
		moneyText->getComponent<Transform>()->setW(strMoney.length() * FONTSIZE / 2);
		moneyTextImage->setTexture(moneyTextTexture);
	}
}

void UIMarket::handleEvents() {
	if (ih->isKeyDown(SDLK_z)) { 
		// si el men?de cesta ya est?abierto, lo cierra
		if (basketMarket->getBasketON())
			basketMarket->setBasketON(false);
		// si el men?de cesta est?cerrado, lo abre
		else
			basketMarket->setBasketON(true);
	}
	else
		Scene::handleEvents();
	/*
	if (ih->isKeyDown(SDLK_SPACE)){
		basketMarket->buyIngredient();
	}
	*/
}

void UIMarket::render() {
	Scene::render();
	if (basketMarket->getBasketON()) {
		basketMarket->getComponent<BasketMarketComponent>()->renderBasket();
	}

}