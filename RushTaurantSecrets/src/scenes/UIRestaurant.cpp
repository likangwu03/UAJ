#include "UIRestaurant.h"

#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../objects/Money.h" // cambiar cuando se cambie la clase Money
#include "../objects/Reputation.h"
#include "../gameObjects/Bin.h"
#include "../objects/Reputation.h"

#include "../utils/checkML.h"

UIRestaurant::UIRestaurant() : Scene() {
	lastTime = sdl->currRealTime();

	// instancia manager del dinero
	GameObject* moneyContainer = new GameObject(this);
	moneyTxt = Money::init(moneyContainer, 200);

	// pensé en hacerlo pasando un struct como parámetro, pero el struct tenía que redefinirse demasiadas veces,
	// así que Cleon me dijo que pasara directamente la información del struct como parámetro

	// icono de reputación
	createGameObjects(grp_ICONS, hdr_REPUTATION, "REPUTATION_ICON", Vector(20, 20), 64, 44, 0);

	// icono de dinero
	createGameObjects(grp_ICONS, hdr_MONEY, "MONEY_ICON", Vector(10, 76), 64, 64, 0);

	// icono de objetivo diario
	createGameObjects(grp_ICONS, hdr_TARGET, "TARGET_ICON", Vector(17, 150), 50, 47, 0);

	// icono de menú del día
	createGameObjects(grp_ICONS, hdr_MENU, "DAILY_MENU_BUTTON", Vector(sdl->width() - 70, sdl->height() - 70), 54, 54, 0);

	// inventario (fondo)
	createGameObjects(grp_ICONS, hdr_INVENTORY, "INVENTORY_ICON", Vector(20, sdl->height() - 244), 80, 224, 0);

	// reloj (momento del día)
	createGameObjects(grp_ICONS, hdr_CLOCK, "CLOCK", Vector(sdl->width() - 140, 20), 120, 117, 0);


	// inventario (platos)
	inventory = new Inventory(this);

	// gestión de la cantidad de dinero
	font = new Font(FONT_PATH, 50);
	moneyText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY_TEXT);
	new Transform(moneyText, Vector(90, 80), Vector(0, 0), 80, 50);

	intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);
	//moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0xFFC863ff));
	moneyTextTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x000000FF));
	moneyTextImage = new Image(moneyText, moneyTextTexture);

	// render de estrellas vacías
	createEmptyStar(Vector(100, 25));
	createEmptyStar(Vector(140, 25));
	createEmptyStar(Vector(180, 25));
	createEmptyStar(Vector(220, 25));
	createEmptyStar(Vector(260, 25));

	reputation = Reputation::instance();

	fullStarTexture = &((*sdl).images().at("STAR"));
	actReputation = reputation->getReputation();

	// inicializa array de estrellas (define qué estrellas se muestran y cuáles no)
	for (int i = 0; i < stars.size(); i++) {
		stars[i] = true;
	}


	// cleon: haced una función/método con parámetros: KISS (keep it simple [stupid]) -> corregido!!
}

UIRestaurant::~UIRestaurant() {
	delete font; // cleon: es imposible que 'f' sea un nombre razonable =D -> corregido!
	delete moneyTextTexture;
	//delete timeTextTexture;
}

void UIRestaurant::createGameObjects(_ecs::_grp_id grp, _ecs::_hdr_id handler, string textureName,
	Vector position, float width, float height, float rotation) {
	GameObject* gameObject = new GameObject(this, grp, handler);
	new Transform(gameObject, position, Vector(0, 0), width, height, rotation);
	new Image(gameObject, &((*sdl).images().at(textureName)));
}

void UIRestaurant::showMoneyText() {
	// si la cantidad de dinero ha variado, lo muestra por pantalla
	if (intMoney != moneyTxt->getMoney()) {
		intMoney = moneyTxt->getMoney();
		std::string strMoney = std::to_string(intMoney);
		delete(moneyTextTexture);
		moneyTextTexture = new Texture(sdl->renderer(), strMoney, *font, build_sdlcolor(0x000000FF));
		moneyTextImage->setTexture(moneyTextTexture);
	}
}

void UIRestaurant::update() {
	Scene::update(); // cleon: falta el delta de tiempo (frametime)
	showMoneyText();
	//checkTime();
	reputationManager();
}

void UIRestaurant::showTimeText() {
	std::string strTime = std::to_string(time);
	delete(timeTextTexture);
	timeTextTexture = new Texture(sdl->renderer(), strTime, *font, build_sdlcolor(0x000000FF));
	timeTextImage->setTexture(timeTextTexture);	
}

void UIRestaurant::checkTime() {
	// NO BORRAR (tomo los antiguos métodos de tiempo como referencia)
	timeT = sdl->currRealTime();
	if (timeT - lastTime >= 1000) {
		time += 1;
		showTimeText();
		lastTime = timeT;
		timeT = 0;
	}
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
	if (actReputation > 80) { // cleon: 80, 60... ¡no! esto provoca guerras y pandemias. CONSTANTES. Constantes son paz y amor.
		stars[0] = true;
		stars[1] = true;
		stars[2] = true;
		stars[3] = true;
		stars[4] = true;
	}

	// si la reputación es mayor de sesenta
	else if (actReputation > 60) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = true;
		stars[3] = true;
		stars[4] = false;
	}

	// si la reputación es mayor de cuarenta
	else if (actReputation > 40) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = true;
		stars[3] = false;
		stars[4] = false;
	}

	// si la reputación es mayor de veinte
	else if (actReputation > 20) {
		stars[0] = true;
		stars[1] = true;
		stars[2] = false;
		stars[3] = false;
		stars[4] = false;
	}

	// si la reputación es mayor de cero
	else if (actReputation > 0) {
		stars[0] = true;
		stars[1] = false;
		stars[2] = false;
		stars[3] = false;
		stars[4] = false;
	}

	// si la reputación es cero o menor
	else if (actReputation < 1) {
		stars[0] = false;
		stars[1] = false;
		stars[2] = false;
		stars[3] = false;
		stars[4] = false;
	}
}

void UIRestaurant::checkRenderStar() {
	for (int i = 0; i < stars.size(); i++) {
		//if (stars[i] == true) {
		if (stars[i]) {
			// estrella 1
			//if (i == 0) { renderStar(100, 25); }

			//// estrella 2
			//else if (i == 1) { renderStar(140, 25); }
			//
			//// estrella 3
			//else if (i == 2) { renderStar(180, 25); }
			//
			//// estrella 4
			//else if (i == 3) { renderStar(220, 25); }
			//
			//// estrella 5
			//else if (i == 4) { renderStar(260, 25); }


			// desplazamiento de 100, y 40 por estrella
			renderStar(100 + i * 40, 25);
		}
	}
}

void UIRestaurant::render() {
	Scene::render();
	checkRenderStar();
}

void UIRestaurant::createEmptyStar(Vector pos) {
	createGameObjects(grp_ICONS, hdr_EMPTY_STAR, "EMPTY_STAR", pos, 30, 32, 0);
}