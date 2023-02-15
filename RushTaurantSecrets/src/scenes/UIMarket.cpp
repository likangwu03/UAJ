#include "UIMarket.h"

UIMarket::UIMarket() : Scene() {
	// icono de dinero
	GameObject* money = new GameObject(this, _ecs::hdr_MONEY, _ecs::grp_ICONS);
	new Transform(money, Vector(20, 80), Vector(0, 0), 50, 50, 0);
	new Image(money, &((*sdl).images().at("MONEY_ICON")));

	// icono de menú del día
	GameObject* menu = new GameObject(this, _ecs::hdr_MENU, _ecs::grp_ICONS);
	new Transform(menu, Vector(sdl->width() - 70, sdl->height() - 70), Vector(0, 0), 50, 50, 0);
	new Image(menu, &((*sdl).images().at("DAILY_MENU")));

	// icono de menú de pausa
	GameObject* pause = new GameObject(this, _ecs::hdr_PAUSE, _ecs::grp_ICONS);
	new Transform(pause, Vector(sdl->width() - 70, 20), Vector(0, 0), 50, 50, 0);
	new Image(pause, &((*sdl).images().at("PAUSE_BUTTON")));

	// icono de cesta
	GameObject* basket = new GameObject(this, _ecs::hdr_BASKET, _ecs::grp_ICONS);
	new Transform(basket, Vector(20, sdl->height() - 70), Vector(0, 0), 50, 50, 0);
	new Image(basket, &((*sdl).images().at("BASKET_YELLOW")));
}