#include "UIMarket.h"

#include "../utils/checkML.h"

UIMarket::UIMarket() : Scene() {
	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = Money::init(moneyContainer, 200);
	ih = InputHandler::instance();
	basketMarket = new BasketMarket(this);

	// icono de dinero
	GameObject* money = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY);
	new Transform(money, Vector(10, 5), Vector(0, 0), 64, 64, 0);
	new Image(money, &((*sdl).images().at("MONEY_ICON")));

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
	GameObject* menu = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MENU);
	new Transform(menu, Vector(sdl->width() - 70, sdl->height() - 70), Vector(0, 0), 50, 50, 0);
	new Image(menu, &((*sdl).images().at("DAILY_MENU_BUTTON")));

	// !! ¿mostrar para indicar la tecla a pulsar para mostrar el menú de pausa?
	// icono de menú de pausa
	//GameObject* pause = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_PAUSE);
	//new Transform(pause, Vector(sdl->width() - 70, 20), Vector(0, 0), 50, 50, 0);
	//new Image(pause, &((*sdl).images().at("PAUSE_BUTTON")));

	// icono de cesta
	GameObject* basket = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_BASKET);
	new Transform(basket, Vector(20, sdl->height() - 90), Vector(0, 0), 68, 70, 0);
	new Image(basket, &((*sdl).images().at("BASKET_YELLOW")));
}

UIMarket::~UIMarket() {
	delete f;
	delete moneyTextTexture;
}


void UIMarket::update() {
	Scene::update();
	showMoneyText();
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