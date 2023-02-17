#include "UIRestaurant.h"

UIRestaurant::UIRestaurant() : Scene() {
	// icono de reputación
	GameObject* reputation = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_REPUTATION);
	new Transform(reputation, Vector(20, 20), Vector(0, 0), 56, 36, 0);
	new Image(reputation, &((*sdl).images().at("REPUTATION_ICON")));

	// icono de dinero
	GameObject* money = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY);
	new Transform(money, Vector(20, 80), Vector(0, 0), 50, 50, 0);
	new Image(money, &((*sdl).images().at("MONEY_ICON")));

	// icono de objetivo diario
	GameObject* target = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_TARGET);
	new Transform(target, Vector(20, 150), Vector(0, 0), 50, 50, 0);
	new Image(target, &((*sdl).images().at("TARGET_ICON")));

	// icono de menú del día
	GameObject* menu = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MENU);
	new Transform(menu, Vector(sdl->width() - 70, sdl->height() - 70), Vector(0, 0), 50, 50, 0);
	new Image(menu, &((*sdl).images().at("DAILY_MENU")));

	// inventario (fondo)
	GameObject* inv = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_INVENTORY);
	new Transform(inv, Vector(20, sdl->height() - 244), Vector(0, 0), 80, 224, 0);
	new Image(inv, &((*sdl).images().at("INVENTORY_ICON")));

	// inventario (platos)
	inventory = new Inventory(this);

	// icono de menú de pausa
	GameObject* pause = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_PAUSE);
	new Transform(pause, Vector(sdl->width() - 70, 20), Vector(0, 0), 50, 50, 0);
	new Image(pause, &((*sdl).images().at("PAUSE_BUTTON")));
	
}

void UIRestaurant::showMoneyText() {
	GameObject* moneyText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY_TEXT);
	Font* f = new Font("assets/Fonts/Hamish.ttf", 50);
	new Transform(moneyText, Vector(90, 80), Vector(0, 0), 80, 50);
	int intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);
	Texture* text = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0xFFC863ff));
	new Image(moneyText, text);
}

void UIRestaurant::update() {
	Scene::update();
	showMoneyText();
}