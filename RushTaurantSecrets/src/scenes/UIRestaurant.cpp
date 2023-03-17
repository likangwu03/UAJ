#include "UIRestaurant.h"

#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../structure/GameManager.h"
#include "../objects/Money.h"
#include "../objects/Reputation.h"
#include "../gameObjects/Bin.h"
#include "../objects/Reputation.h"
#include "../components/Warning.h"
#include "../components/BoxText.h"

#include "../utils/checkML.h"

UIRestaurant::UIRestaurant() : Scene() {
	lastTime = sdl->currRealTime();

	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = GameManager::instance()->getMoney();

	// pensé en hacerlo pasando un struct como parámetro, pero el struct tenía que redefinirse demasiadas veces,
	// así que Cleon me dijo que pasara directamente la información del struct como parámetro

	// icono de reputación
	createIcon("REPUTATION_ICON", Vector(ICONX, ICONY), ICONSIZE, ICONSIZE, 0, grp_ICONS, hdr_REPUTATION);

	// icono de dinero
	createIcon("MONEY_ICON", Vector(ICONX, ICONY * 2 + ICONSIZE), ICONSIZE, ICONSIZE, 0, grp_ICONS, hdr_MONEY);

	// icono de objetivo diario
	createIcon("TARGET_ICON", Vector(ICONX, ICONY * 3 + ICONSIZE * 2), ICONSIZE, ICONSIZE, 0, grp_ICONS, hdr_TARGET);

	// icono de menú del día
	createIcon("DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), ICONSIZE, ICONSIZE, 0, grp_ICONS, hdr_MENU);

	// inventario (fondo)
	createIcon("INVENTORY_ICON", Vector(ICONX, sdl->height() - 302 - ICONX), 82, 302, 0, grp_ICONS, hdr_INVENTORY);

	// inventario (platos)
	inventory = new Inventory(this);

	// gestión de la cantidad de dinero
	intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);

	font = new Font(FONT_PATH, FONTSIZE);
	moneyTextTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x000000FF));
	moneyText = createIcon(moneyTextTexture, Vector(80, ICONY * 2 + ICONSIZE - 5), strMoney.length() * FONTSIZE / 2, FONTSIZE, 0, _ecs::grp_ICONS, _ecs::hdr_MONEY_TEXT);
	moneyTextImage = new Image(moneyText, moneyTextTexture);

	// render de estrellas vacías
	for (int i = 0; i < stars.size(); i++) 
		createIcon("EMPTY_STAR", Vector(80 + i * 40, 25), 30, 32, 0, grp_ICONS, hdr_EMPTY_STAR);


	reputation = GameManager::instance()->getReputation();

	fullStarTexture = &((*sdl).images().at("STAR"));
	actReputation = reputation->getReputation();

	// inicializa array de estrellas (define qué estrellas se muestran y cuáles no)
	for (int i = 0; i < stars.size(); i++) {
		stars[i] = true;
	}

	float frequency = 1000;
	GameObject* thiefExclamation = createIcon("EXCLAMATION", Vector(640, 85), 32, 32);
	new Warning(thiefExclamation, frequency);

	intObjective = 30;
	objectiveTextTexture = new Texture(sdl->renderer(), std::to_string(intObjective), *font, build_sdlcolor(0x000000FF));
	createIcon(objectiveTextTexture, Vector(80, ICONY * 3 + ICONSIZE * 2), std::to_string(intObjective).length() * FONTSIZE / 2, FONTSIZE, 0, _ecs::grp_ICONS);
	
	GameObject* prueba = new GameObject(this);
	new BoxText(prueba, { "Al venir al mundo fueron delicadamente mecidas por las manos de la lustral Doniazada, su buena tia, que grabo sus nombres sobre hojas de oro coloreadas de humedas pedrerias y las cuido bajo el terciopelo de sus pupilas hasta la adolescencia dura.", "Holaaa holaaa" }, 30, 30, Vector(200, 100), 0.2 * 1000, FONT_PATH, FONTSIZE, 700);

	clock = new Clock(this);
}

UIRestaurant::~UIRestaurant() {
	delete font;
	delete moneyTextTexture;
	delete objectiveTextTexture;
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

void UIRestaurant::showMoneyText() {
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

void UIRestaurant::update() {
	Scene::update(); // cleon: falta el delta de tiempo (frametime)
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

void UIRestaurant::render() {
	Scene::render();
	checkRenderStar();
}