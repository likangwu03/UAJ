#include "UIRestaurant.h"

#include "../utils/checkML.h"

UIRestaurant::UIRestaurant() : Scene() {
	lastTime = sdl->currRealTime();

	// icono de reputación
	GameObject* reputation = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_REPUTATION);
	new Transform(reputation, Vector(20, 20), Vector(0, 0), 56, 36, 0);
	new Image(reputation, &((*sdl).images().at("REPUTATION_ICON")));

	// icono de dinero
	GameObject* money = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY);
	new Transform(money, Vector(10, 76), Vector(0, 0), 64, 64, 0);
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

	// gestión de la cantidad de dinero
	f = new Font("assets/Fonts/Hamish.ttf", 50);
	moneyText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY_TEXT);
	new Transform(moneyText, Vector(90, 80), Vector(0, 0), 80, 50);
	intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);
	moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0xFFC863ff));
	moneyTextImage = new Image(moneyText, moneyTextTexture);

	// gestión del temporizador
	timeText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_TIME_TEXT);
	new Transform(timeText, Vector(sdl->width() - 70, 80), Vector(0, 0), 50, 50);
	std::string strTime = std::to_string(time);
	timeTextTexture = new Texture(sdl->renderer(), strTime, *f, build_sdlcolor(0x000000FF));
	timeTextImage = new Image(timeText, timeTextTexture);
}

void UIRestaurant::showMoneyText() {
	// si la cantidad de dinero ha variado, lo muestra por pantalla
	if (intMoney != moneyTxt->getMoney()) {
		intMoney = moneyTxt->getMoney();
		std::string strMoney = std::to_string(intMoney);
		delete(moneyTextTexture);
		moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0x000000FF));
		moneyTextImage->setTexture(moneyTextTexture);
	}
}

void UIRestaurant::update() {
	Scene::update();
	showMoneyText();
	checkTime();
}

void UIRestaurant::showTimeText() {
	std::string strTime = std::to_string(time);
	delete(timeTextTexture);
	timeTextTexture = new Texture(sdl->renderer(), strTime, *f, build_sdlcolor(0x000000FF));
	timeTextImage->setTexture(timeTextTexture);	
}

void UIRestaurant::checkTime() {
	timeT = sdl->currRealTime();
	if (timeT - lastTime >= 1000) {
		time += 1;
		showTimeText();
		lastTime = timeT;
		timeT = 0;
	}
}