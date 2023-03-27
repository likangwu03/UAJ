#include "UIRestaurant.h"

#include "../Structure/GameObject.h"
#include "../Structure/GameManager.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/Warning.h"
#include "../Managers/Money.h"
#include "../Managers/Reputation.h"
#include "../GameObjects/DailyMenu.h"
#include "../GameObjects/Bin.h"
#include "../GameObjects/Dialogue.h"
#include "../GameObjects/ButtonGO.h"
#include "../GameObjects/FreeText.h"
#include "../Components/Streak.h"
#include "../Managers/DayManager.h"
#include "../Utilities/checkML.h"

UIRestaurant::UIRestaurant() : Scene() {
	lastTime = sdl->currRealTime();

	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = GameManager::get()->getMoney();

	// pensé en hacerlo pasando un struct como parámetro, pero el struct tenía que redefinirse demasiadas veces,
	// así que Cleon me dijo que pasara directamente la información del struct como parámetro
	
	// Reputación
	reputation = GameManager::get()->getReputation();
	// icono 
	createIcon("REPUTATION_ICON", Vector(ICONX, ICONY), ICONSIZE, ICONSIZE, 0, grp_ICONS);
	// estrellas vacías
	for (int i = 0; i < stars.size(); i++) 
		createIcon("EMPTY_STAR", Vector(80 + i * 40, 25), 30, 32, 0, grp_ICONS);

	fullStarTexture = &((*sdl).images().at("STAR"));
	actReputation = reputation->getReputation();

	// inicializa array de estrellas (define qué estrellas se muestran y cuáles no)
	for (int i = 0; i < stars.size(); i++) {
		stars[i] = true;
	}


	// Fuente
	font = new Font(FONT_PATH, FONTSIZE);
	outline = new Font(FONT_PATH, FONTSIZE);
	TTF_SetFontOutline(outline->getTTFFont(), 2);


	// Dinero
	intMoney = moneyTxt->getMoney();
	// icono
	createIcon("MONEY_ICON", Vector(ICONX, ICONY * 2 + ICONSIZE), ICONSIZE, ICONSIZE, 0, grp_ICONS);
	// Texto
	std::string strMoney = std::to_string(intMoney);
	moneyTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x3a3a50FF));
	moneyOutline = new Texture(sdl->renderer(), strMoney, *outline, build_sdlcolor(0xFFFFFFFF));
	moneyRect = { 80, (int)(ICONY * 2 + ICONSIZE - 5), moneyTexture->width() ,moneyTexture->height() };
	moneyOutlineRect = moneyRect;
	moneyOutlineRect.x -= CENTEROUTLINE/2; moneyOutlineRect.w += CENTEROUTLINE;
	moneyOutlineRect.y -= CENTEROUTLINE/2; moneyOutlineRect.h += CENTEROUTLINE;


	// inventario (fondo)
	createIcon("INVENTORY_ICON", Vector(ICONX, sdl->height() - 302 - ICONX), 82, 302, 0, grp_ICONS);

	// inventario (platos)
	inventory = new Inventory(this);

	// Exclamación de la despensa
	float frequency = 1000;
	GameObject* thiefExclamation = createIcon("EXCLAMATION", Vector(640, 85), 32, 32);
	new Warning(thiefExclamation, frequency);
	
	new Dialogue(this, Vector(150, 520), 700, 0.01 * 1000, font, &sdl->images().at("MAIN_CHARACTER_PORTRAIT"), { "Hi, this a demo of ResTaurant Secrets.", "Have fun cooking and killing people."});
	//new FreeText(this, Vector(300, 300), 20, 30, 500, 0.01 * 1000, font, { "Al venir al mundo fueron delicadamente mecidas por las manos de la lustral Doniazada, su buena tia.", "Hola hola hola hola me llamo \n Pedro" });

	// Racha de cobros
	GameObject* streak = new GameObject(this, _ecs::grp_HUD, _ecs::hdr_STREAK);
	new Streak(streak, 10, Vector(820, 260), 430, 30, 2, font);

	// Reloj
	new Clock(this);
}

UIRestaurant::~UIRestaurant() {
	delete font;
	delete outline;
	delete moneyTexture;
	delete moneyOutline;
	delete objectiveTexture;
	delete objectiveOutline;
}

void UIRestaurant::callAfterCreating() {
	// Objetivo diario
	intObjective = GameManager::get()->getDayManager()->getDailyObjective(); moneyDiff = 0;
	// Icono
	createIcon("TARGET_ICON", Vector(ICONX, ICONY * 3 + ICONSIZE * 2), ICONSIZE, ICONSIZE, 0, grp_ICONS);
	// Texto
	std::string strObjective = "0/" + std::to_string(intObjective);
	objectiveTexture = new Texture(sdl->renderer(), strObjective, *font, build_sdlcolor(0x3a3a50FF));
	objectiveOutline = new Texture(sdl->renderer(), strObjective, *outline, build_sdlcolor(0xFFFFFFFF));
	objectiveRect = { 80, (int)(ICONY * 3 + ICONSIZE * 2), objectiveTexture->width(), objectiveTexture->height() };
	objectiveOutlineRect = objectiveRect;
	objectiveOutlineRect.x -= CENTEROUTLINE / 2; objectiveOutlineRect.w += CENTEROUTLINE;
	objectiveOutlineRect.y -= CENTEROUTLINE / 2; objectiveOutlineRect.h += CENTEROUTLINE;
}

GameObject* UIRestaurant::dataIcon(Texture* texture, Vector position, float width, float height, float rotation,
	_ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID) {

	GameObject* gameObject = new GameObject(this, grp, handler);
	new Transform(gameObject, position, Vector(0, 0), width, height, rotation);
	new Image(gameObject, texture);

	return gameObject;
}

GameObject* UIRestaurant::createIcon(string textureName, Vector position, float width, float height, float rotation,
	_ecs::_grp_id grp, _ecs::_hdr_id handler) {

	return dataIcon(&((*sdl).images().at(textureName)), position, width, height, rotation, grp, handler);
}

GameObject* UIRestaurant::createIcon(Texture* texture, Vector position, float width, float height, float rotation,
	_ecs::_grp_id grp, _ecs::_hdr_id handler) {

	return dataIcon(texture, position, width, height, rotation, grp, handler);
}

void UIRestaurant::toggleDailyMenu()
{
	menuToggled = !menuToggled;
	menu->getComponent<Transform>()->setActive(menuToggled);
	menu->getComponent<Image>()->setActive(menuToggled);
	menu->getComponent<DailyMenuComp>()->setActive(menuToggled);
}

void UIRestaurant::showMoneyText() {
	// si la cantidad de dinero ha variado, lo muestra por pantalla
	if (intMoney != moneyTxt->getMoney()) {
		moneyDiff += moneyTxt->getMoney() - intMoney;
		intMoney = moneyTxt->getMoney();
		std::string strMoney = std::to_string(intMoney);
		
		delete moneyTexture;
		delete moneyOutline;
		moneyTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x3a3a50FF));
		moneyOutline = new Texture(sdl->renderer(), strMoney, *outline, build_sdlcolor(0xFFFFFFFF));
		moneyRect = { 80, (int)(ICONY * 2 + ICONSIZE - 5), moneyTexture->width() ,moneyTexture->height() };
		moneyOutlineRect = moneyRect;
		moneyOutlineRect.x -= CENTEROUTLINE/2; moneyOutlineRect.w += CENTEROUTLINE;
		moneyOutlineRect.y -= CENTEROUTLINE/2; moneyOutlineRect.h += CENTEROUTLINE;

		delete objectiveTexture;
		delete objectiveOutline;
		std::string strObj = std::to_string(moneyDiff) + "/" + std::to_string(intObjective);
		objectiveTexture = new Texture(sdl->renderer(), strObj, *font, build_sdlcolor(0x3a3a50FF));
		objectiveOutline = new Texture(sdl->renderer(), strObj, *outline, build_sdlcolor(0xFFFFFFFF));
		objectiveRect = { 80, (int)(ICONY * 3 + ICONSIZE * 2), objectiveTexture->width(), objectiveTexture->height() };
		objectiveOutlineRect = objectiveRect;
		objectiveOutlineRect.x -= CENTEROUTLINE/2; objectiveOutlineRect.w += CENTEROUTLINE;
		objectiveOutlineRect.y -= CENTEROUTLINE/2; objectiveOutlineRect.h += CENTEROUTLINE;
	}
}

void UIRestaurant::update() {
	Scene::update();
	showMoneyText();
	//checkTime();
	reputationManager();
	//updateClock();
}

void UIRestaurant::renderStar(int x, int y) {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = 30;
	dest.h = 32;

	// renderiza la textura
	fullStarTexture->render(dest);
}

void UIRestaurant::reputationManager() {
	// comprueba si la reputación ha cambiado
	actReputation = reputation->getReputation();
	checkStarsArray();	
}

void UIRestaurant::checkStarsArray() {
	// si la reputación es mayor de ochenta
	if (actReputation > REP5) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = true;
		stars[3] = true;
		stars[4] = true;
	}

	// si la reputación es mayor de sesenta
	else if (actReputation > REP4) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = true;
		stars[3] = true;
		stars[4] = false;
	}

	// si la reputación es mayor de cuarenta
	else if (actReputation > REP3) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = true;
		stars[3] = false;
		stars[4] = false;
	}

	// si la reputación es mayor de veinte
	else if (actReputation > REP2) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = false;
		stars[3] = false;
		stars[4] = false;
	}

	// si la reputación es mayor de cero
	else if (actReputation > REP1) {
		stars[0] = true;
		stars[1] = false;
		stars[2] = false;
		stars[3] = false;
		stars[4] = false;
	}

	// si la reputación es cero o menor
	else if (actReputation < REP0) {
		stars[0] = false;
		stars[1] = false;
		stars[2] = false;
		stars[3] = false;
		stars[4] = false;
	}
}

void UIRestaurant::checkRenderStar() {
	for (int i = 0; i < stars.size(); i++) {
		if (stars[i]) {
			// desplazamiento de 80, y 40 por estrella
			renderStar(80 + i * 40, 25);
		}
	}
}

void UIRestaurant::setDailyMenu() {
	//menú del día
	menu = new DailyMenu(this, "DAILY_MENU", Vector((sdlutils().width() / 2) - 239.5f, 30),
		479.0f, 640.0f, GameManager::get()->getTodaysMenu(), []() {});
	menuToggled = true;
	toggleDailyMenu();
	menu->getComponent<ButtonComp>()->setActive(false);

	// icono de menú del día
	//createIcon("DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), ICONSIZE, ICONSIZE, 0, grp_ICONS);
	new ButtonGO(this, "DAILY_MENU_BUTTON", "DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), ICONSIZE, ICONSIZE,
		[&]() {
			toggleDailyMenu();
		});

	//menu->getComponent<DailyMenuComp>()->setMenu(_menu);
	//dmen = menu->getComponent<DailyMenuComp>()->getMenu();
}

void UIRestaurant::render() {
	moneyOutline->render(moneyOutlineRect);
	moneyTexture->render(moneyRect);

	objectiveOutline->render(objectiveOutlineRect);
	objectiveTexture->render(objectiveRect);
	
	Scene::render();
	checkRenderStar();
}