#include "UIMarket.h"

#include "../utils/checkML.h"

UIMarket::UIMarket() : Scene() {
	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = Money::init(moneyContainer, 200);
	ih = InputHandler::instance();
	basketMarket = new BasketMarket(this);

	// icono de dinero
	createGameObjects(_ecs::grp_ICONS, _ecs::hdr_MONEY, "MONEY_ICON", Vector(10, 5), 64, 64, 0);

	// gestión de la cantidad de dinero
	f = new Font(FONT_PATH, 50);
	moneyText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY_TEXT);
	new Transform(moneyText, Vector(90, 9), Vector(0, 0), 80, 50);

	intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);
	//moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0xFFC863ff));
	moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0x000000FF));
	moneyTextImage = new Image(moneyText, moneyTextTexture);

	// icono de menú del día
	createGameObjects(_ecs::grp_ICONS, _ecs::hdr_MENU, "DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), 50, 50, 0);

	// icono de cesta
	createGameObjects(_ecs::grp_ICONS, _ecs::hdr_BASKET, "BASKET_YELLOW", Vector(20, sdl->height() - 90), 68, 70, 0);
}

UIMarket::~UIMarket() {
	delete f;
	delete moneyTextTexture;
}


void UIMarket::update() {
	Scene::update();
	showMoneyText();
}

void UIMarket::createGameObjects(_ecs::_grp_id grp, _ecs::_hdr_id handler, string textureName,
	Vector position, float width, float height, float rotation) {
	GameObject* gameObject = new GameObject(this, grp, handler);
	new Transform(gameObject, position, Vector(0, 0), width, height, rotation);
	new Image(gameObject, &((*sdl).images().at(textureName)));
}


void UIMarket::showMoneyText() {
	// si la cantidad de dinero ha variado, lo muestra por pantalla
	if (intMoney != moneyTxt->getMoney()) {
		intMoney = moneyTxt->getMoney();
		std::string strMoney = std::to_string(intMoney);
		delete(moneyTextTexture);
		moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0x000000FF));
		moneyTextImage->setTexture(moneyTextTexture);
	}
}

void UIMarket::handleEvents() {
	if (ih->isKeyDown(SDLK_SPACE)) { 
		// si el menú de cesta ya está abierto, lo cierra
		if (basketMarket->getBasketON())
			basketMarket->setBasketON(false);
		// si el menú de cesta está cerrado, lo abre
		else
			basketMarket->setBasketON(true);
	}
	else
		Scene::handleEvents();
}

void UIMarket::render() {
	Scene::render();
	if (basketMarket->getBasketON()) 
		basketMarket->getComponent<BasketMarketComponent>()->renderBasket();
}