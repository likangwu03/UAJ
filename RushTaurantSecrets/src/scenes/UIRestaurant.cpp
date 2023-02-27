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


	// cleon: haced una función/método con parámetros: KISS (keep it simple [stupid])
	// icono de reputación
	GameObject* reputationIcon = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_REPUTATION);
	new Transform(reputationIcon, Vector(20, 20), Vector(0, 0), 64, 44, 0);
	new Image(reputationIcon, &((*sdl).images().at("REPUTATION_ICON")));

	// icono de dinero
	GameObject* money = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY);
	new Transform(money, Vector(10, 76), Vector(0, 0), 64, 64, 0);
	new Image(money, &((*sdl).images().at("MONEY_ICON")));

	// icono de objetivo diario
	GameObject* target = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_TARGET);
	new Transform(target, Vector(17, 150), Vector(0, 0), 50, 47, 0);
	new Image(target, &((*sdl).images().at("TARGET_ICON")));

	// icono de menú del día
	GameObject* menu = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MENU);
	new Transform(menu, Vector(sdl->width() - 70, sdl->height() - 70), Vector(0, 0), 54, 54, 0);
	new Image(menu, &((*sdl).images().at("DAILY_MENU_BUTTON")));

	// inventario (fondo)
	GameObject* inv = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_INVENTORY);
	new Transform(inv, Vector(20, sdl->height() - 244), Vector(0, 0), 80, 224, 0);
	new Image(inv, &((*sdl).images().at("INVENTORY_ICON")));

	// inventario (platos)
	inventory = new Inventory(this);

	/*// icono de reloj (temporizador)
	GameObject* clock = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_CLOCK);
	new Transform(clock, Vector(sdl->width() - 70, 20), Vector(0, 0), 60, 57, 0);
	new Image(clock, &((*sdl).images().at("CLOCK_ICON")));*/

	// reloj (momento del día)
	GameObject* clock = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_CLOCK);
	new Transform(clock, Vector(sdl->width() - 140, 20), Vector(0, 0), 120, 117, 0);
	new Image(clock, &((*sdl).images().at("CLOCK")));

	// 

	// !! ¿mostrar para indicar la tecla a pulsar para mostrar el menú de pausa?
	// icono de menú de pausa
	//GameObject* pause = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_PAUSE);
	//new Transform(pause, Vector(sdl->width() - 70, 20), Vector(0, 0), 50, 50, 0);
	//new Image(pause, &((*sdl).images().at("PAUSE_BUTTON")));

	// gestión de la cantidad de dinero
	f = new Font(FONT_PATH, 50);
	moneyText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_MONEY_TEXT);
	new Transform(moneyText, Vector(90, 80), Vector(0, 0), 80, 50);

	intMoney = moneyTxt->getMoney();
	std::string strMoney = std::to_string(intMoney);
	//moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0xFFC863ff));
	moneyTextTexture = new Texture(sdl->renderer(), strMoney, *f, build_sdlcolor(0x000000FF));
	moneyTextImage = new Image(moneyText, moneyTextTexture);

	// gestión del temporizador
	/*timeText = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_TIME_TEXT);
	new Transform(timeText, Vector(sdl->width() - 140, 25), Vector(0, 0), 50, 50);
	std::string strTime = std::to_string(time);
	timeTextTexture = new Texture(sdl->renderer(), strTime, *f, build_sdlcolor(0x000000FF));
	timeTextImage = new Image(timeText, timeTextTexture);*/


	// render de estrellas vacías
	GameObject* emptyStar1 = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_EMPTY_STAR);
	new Transform(emptyStar1, Vector(100, 25), Vector(0,0), 30, 32);
	new Image(emptyStar1, &((*sdl).images().at("EMPTY_STAR")));

	GameObject* emptyStar2 = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_EMPTY_STAR);
	new Transform(emptyStar2, Vector(140, 25), Vector(0, 0), 30, 32);
	new Image(emptyStar2, &((*sdl).images().at("EMPTY_STAR")));

	GameObject* emptyStar3 = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_EMPTY_STAR);
	new Transform(emptyStar3, Vector(180, 25), Vector(0, 0), 30, 32);
	new Image(emptyStar3, &((*sdl).images().at("EMPTY_STAR")));

	GameObject* emptyStar4 = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_EMPTY_STAR);
	new Transform(emptyStar4, Vector(220, 25), Vector(0, 0), 30, 32);
	new Image(emptyStar4, &((*sdl).images().at("EMPTY_STAR")));

	GameObject* emptyStar5 = new GameObject(this, _ecs::grp_ICONS, _ecs::hdr_EMPTY_STAR);
	new Transform(emptyStar5, Vector(260, 25), Vector(0, 0), 30, 32);
	new Image(emptyStar5, &((*sdl).images().at("EMPTY_STAR")));

	reputation = Reputation::instance();

	fullStarTexture = &((*sdl).images().at("STAR"));
	actReputation = reputation->getReputation();

	// inicializa array de estrellas (define qué estrellas se muestran y cuáles no)
	for (int i = 0; i < stars.size(); i++) {
		stars[i] = true;
	}
}


UIRestaurant::~UIRestaurant() {
	delete f; // cleon: es imposible que 'f' sea un nombre razonable =D
	delete moneyTextTexture;
	//delete timeTextTexture;
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
	Scene::update(); // cleon: falta el delta de tiempo (frametime)
	showMoneyText();
	//checkTime();
	reputationManager();
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