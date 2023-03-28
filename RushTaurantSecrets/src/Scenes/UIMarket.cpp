#include "UIMarket.h"
#include "../Structure/GameManager.h"
#include "../Managers/Money.h"

#include "../Components/ShoppingMenuComp.h"
#include "../Utilities/checkML.h"

void UIMarket::toggleDailyMenu() {
	menuToggled = !menuToggled;
	menu->getComponent<Transform>()->setActive(menuToggled);
	menu->getComponent<Image>()->setActive(menuToggled);
	menu->getComponent<DailyMenuComp>()->setActive(menuToggled);
}

UIMarket::UIMarket(Scene* market) : Scene(),market(market) {
	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = GameManager::get()->getMoney();
	ih = InputHandler::instance();
	basketMarket = new BasketMarket(this);

	// Fuente
	font = new Font(FONT_PATH, FONTSIZE);
	outline = new Font(FONT_PATH, FONTSIZE);
	TTF_SetFontOutline(outline->getTTFFont(), 2);

	// Dinero
	intMoney = moneyTxt->getMoney();
	// icono
	createGameObjects(_ecs::grp_ICONS, "MONEY_ICON", Vector(ICONX, ICONY), ICONSIZE, ICONSIZE, 0);
	// Texto
	std::string strMoney = std::to_string(intMoney);
	moneyTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x3a3a50FF));
	moneyOutline = new Texture(sdl->renderer(), strMoney, *outline, build_sdlcolor(0xFFFFFFFF));
	moneyRect = { 80, (int)(ICONY - 2), moneyTexture->width() ,moneyTexture->height() };
	moneyOutlineRect = moneyRect;
	moneyOutlineRect.x -= CENTEROUTLINE / 2; moneyOutlineRect.w += CENTEROUTLINE;
	moneyOutlineRect.y -= CENTEROUTLINE / 2; moneyOutlineRect.h += CENTEROUTLINE;


	// icono de cesta
	createGameObjects(_ecs::grp_ICONS, "BASKET_YELLOW", Vector(20, sdl->height() - 90), 68, 70, 0);

	//men¨² de compra
	shopMenu = new GameObject(this, _ecs::grp_GENERAL, hdr_SHOP_MENU1);
	new ShoppingMenuComp(shopMenu);

	// icono de menú del día
	menuToggled = true;
	menu = new DailyMenu(this, "DAILY_MENU", Vector((sdlutils().width() / 2) - 239.5f, 30),
		479.0f, 640.0f, []() {});
	menu->getComponent<ButtonComp>()->setActive(false);
	toggleDailyMenu();
	new ButtonGO(this, "DAILY_MENU_BUTTON", "DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), ICONSIZE, ICONSIZE,
		[&]() {
			toggleDailyMenu();
		});
}

UIMarket::~UIMarket() {
	delete font;
	delete outline;
	delete moneyTexture;
	delete moneyOutline;
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
		
		delete moneyTexture;
		delete moneyOutline;
		moneyTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x3a3a50FF));
		moneyOutline = new Texture(sdl->renderer(), strMoney, *outline, build_sdlcolor(0xFFFFFFFF));
		moneyRect = { 80, (int)(ICONY - 2), moneyTexture->width() ,moneyTexture->height() };
		moneyOutlineRect = moneyRect;
		moneyOutlineRect.x -= CENTEROUTLINE / 2; moneyOutlineRect.w += CENTEROUTLINE;
		moneyOutlineRect.y -= CENTEROUTLINE / 2; moneyOutlineRect.h += CENTEROUTLINE;
	}
}

void UIMarket::handleEvents() {
	if (ih->isKeyDown(SDLK_z)) { 
		// si el men?de cesta ya est?abierto, lo cierra
		if (basketMarket->getComponent<BasketMarketComponent>()->getBasketON())
			basketMarket->getComponent<BasketMarketComponent>()->setBasketON(false);
		// si el men?de cesta est?cerrado, lo abre
		else
			basketMarket->getComponent<BasketMarketComponent>()->setBasketON(true);
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
	moneyOutline->render(moneyOutlineRect);
	moneyTexture->render(moneyRect);

	Scene::render();
	if (basketMarket->getComponent<BasketMarketComponent>()->getBasketON()) {
		basketMarket->getComponent<BasketMarketComponent>()->renderBasket();
	}

}

void UIMarket::setDailyMenu() {
	menu->getComponent<DailyMenuComp>()->setMenu(GameManager::instance()->getTodaysMenu());
}

