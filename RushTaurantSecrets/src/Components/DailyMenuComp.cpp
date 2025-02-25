#include "DailyMenuComp.h"
#include "../Utilities/checkML.h"

/*
Area donde pueden haber ingredientes: 450, 388 (512)
Cada plato tiene dos filas de 48px para renderizar los platos.
Se mira el número de ingredientes que tiene el plato, si es > 4 se renderiza en dos filas,
si no, se renderiza en una
*/

void DailyMenuComp::drawDishes() {

	Vector t = tf->getPos();

	//se dibujan los platos
	for (int i = 0; i < menu->size(); ++i) {
		//textura plato
		Texture* plateTex = &((*SDLUtils::instance()).images().at(std::to_string(menu->at(i).id)));
		float dishx = t.getX() + (DISH_SIZE)+STARTING_X;
		float dishy = (t.getY() * 4) + (i * (INGREDIENT_SIZE * 2.3) + STARTING_Y);
		dishTextures.push_back({ plateTex, dishx, dishy });
		//textura "="
		std::string equalString = ("=");
		float equalX = t.getX() + (DISH_SIZE * 1.75f) + FONT_SIZE + STARTING_X;
		Texture* equalTex = new Texture(sdlutils().renderer(), equalString, *font, build_sdlcolor(0x725644FF));
		menuText.push_back({ equalTex, equalX, dishy + (DISH_SIZE / 2) - 5 });

		int temp = 0;
		int count = 0;
		//se dibujan los ingredientes
		for (auto ing : menu->at(i).ingredients) {
			float ingx = equalX + 2 * ING_OFFSET_X;
			float ingy = dishy;
			float plusx = ingx + INGREDIENT_SIZE + ING_OFFSET_X;
			float ingDistance = plusx - ingx;
			if (count > 2) {
				if (temp > 2)
					temp = 0;
				ingx = equalX + ingDistance;
				plusx = ingx + INGREDIENT_SIZE + ING_OFFSET_X;
				ingy += INGREDIENT_SIZE;
			}
			Texture* ingTex = &((*SDLUtils::instance()).images().at(std::to_string(ing)));
			ingTextures.push_back({ ingTex, ingx + (ingDistance + INGREDIENT_SIZE / 2) * temp, ingy + INGREDIENT_SIZE / 5 });

			std::string plusString = ("+");
			Texture* plusTex = new Texture(sdlutils().renderer(), plusString, *font, build_sdlcolor(0x725644FF));
			menuText.push_back({ plusTex, plusx + (ingDistance + INGREDIENT_SIZE / 2) * temp, ingy + (DISH_SIZE / 2) - 5 });

			++temp;
			++count;
		}
		//se quita el ultimo +
		delete menuText.back().tex;
		menuText.pop_back();

		//se dibuja el precio
		std::string priceString = (std::to_string(menu->at(i).price) + "$");
		float textX = t.getX() + (DISH_SIZE * 6.7) + STARTING_X;
		float textY = dishy + FONT_SIZE;

		Texture* tempOutline = new Texture(sdlutils().renderer(), priceString, *fontOutline, build_sdlcolor(0xa2770dFF));
		tempOutline->setWidth((tempOutline->width() + CENTER_OUTLINE) * TEXT_RESIZE);
		tempOutline->setHeigth((tempOutline->height() + CENTER_OUTLINE) * TEXT_RESIZE);

		textOutlines.push_back({ tempOutline, textX - CENTER_OUTLINE, textY - CENTER_OUTLINE });

		Texture* tempTex = new Texture(sdlutils().renderer(), priceString, *font, build_sdlcolor(0xffbb11FF));
		tempTex->setWidth(tempTex->width() * TEXT_RESIZE);
		tempTex->setHeigth(tempTex->height() * TEXT_RESIZE);
		textTextures.push_back({ tempTex, textX, textY });

	}
}

void DailyMenuComp::randomMenu() {
	//set para evitar que hayan dos platos iguales en el mismo menu
	set<uint8_t> aux;
	vector<_ecs::DishInfo> temp;
	int dish;

	int i = 0;
	//si el jugador ha matado a alguien se a�ade un plato de carne aleatorio
	if (GameManager::get()->getHasKill()) {
		dish = rand() % _ecs::NUM_MEAT_DISH;
		aux.insert(_ecs::MeatDishes[dish].id);
		menu->push_back(_ecs::MeatDishes[dish]);
		++i;
	}
	// Menu del dia aleatorio (lo rellena con 4 platos diferentes
	// entre si y los pasa a un vector para poder acceder a ellos)
	// aux sirve para asegurarse de que no se inserta dos veces el mismo plato en el menu

	while (i < MENU_SIZE) {
		dish = rand() % _ecs::NUM_DISH;
		if (aux.insert(_ecs::Dishes[dish].id).second) {
			menu->push_back(_ecs::Dishes[dish]);
			i++;
		}
	}
}

void DailyMenuComp::init() {
	drawDishes();
}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id)
	: Component(parent, id)
{
	tf = parent->getComponent<Transform>();
	parentScene = parent->getScene();

	font = new Font(FONT_PATH, FONT_SIZE);
	fontOutline = new Font(FONT_PATH, FONT_SIZE);
	TTF_SetFontOutline(fontOutline->getTTFFont(), 2);
	initialized = true;
	menu = nullptr;

}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, vector<_ecs::DishInfo>* _menu)
	: Component(parent, id), tf(nullptr), parentScene(nullptr), initialized(false), menu(_menu), font(nullptr), fontOutline(nullptr)
{
}

void DailyMenuComp::initMenu() {
	menu = new vector<_ecs::DishInfo>();
	//randomMenu();
	testMenu();
	init();
}

DailyMenuComp::~DailyMenuComp() {
	if (initialized) delete menu;
	for (auto e : menuText) delete e.tex;
	for (auto e : textTextures) delete e.tex;
	for (auto e : textOutlines) delete e.tex;
	delete font;
	delete fontOutline;
}

void DailyMenuComp::render() {
	for (auto e : dishTextures)
		e.tex->render(build_sdlrect(e.x, e.y, DISH_SIZE, DISH_SIZE));
	for (auto i : ingTextures)
		i.tex->render(build_sdlrect(i.x, i.y, INGREDIENT_SIZE, INGREDIENT_SIZE));
	for (auto p : menuText)
		p.tex->render(build_sdlrect(p.x, p.y, 15, FONT_SIZE));
	for (auto t : textOutlines)
		t.tex->render(build_sdlrect(t.x, t.y, t.tex->width(), t.tex->height()));
	for (auto t : textTextures)
		t.tex->render(build_sdlrect(t.x, t.y, t.tex->width(), t.tex->height()));
}

vector<_ecs::DishInfo>* DailyMenuComp::getMenu()
{
	return menu;
}

void DailyMenuComp::setMenu(vector<_ecs::DishInfo>* _menu)
{
	//se borran los platos anteriores y se indica que ya se han asignado platos
	
	initialized = false;
	for (auto e : menuText) delete e.tex;
	for (auto e : textTextures) delete e.tex;
	for (auto e : textOutlines) delete e.tex;
	menuText.clear();
	textTextures.clear();
	textOutlines.clear();
	dishTextures.clear();
	ingTextures.clear();
	menu = _menu;
	//se dibujan de nuevo los platos
	drawDishes();
}

void DailyMenuComp::testMenu()
{
	menu->push_back(_ecs::Dishes[_ecs::ICE_CREAM]);
	menu->push_back(_ecs::Dishes[_ecs::ROASTED_CHICKEN]);
	menu->push_back(_ecs::Dishes[_ecs::CURRY_RICE]);
	menu->push_back(_ecs::Dishes[_ecs::HOTDOG]);

}

void DailyMenuComp::initMenu(const vector<uint8_t>& menu_) {
	menu->clear();
	for (uint8_t d : menu_) {
		if (d <= _ecs::NUM_DISH)menu->push_back(_ecs::Dishes[d]);
		else menu->push_back(_ecs::MeatDishes[d- _ecs::NUM_DISH]);
	}
	//se borran los platos anteriores y se indica que ya se han asignado platos
	initialized = false;
	for (auto e : menuText) delete e.tex;
	for (auto e : textTextures) delete e.tex;
	for (auto e : textOutlines) delete e.tex;
	menuText.clear();
	textTextures.clear();
	textOutlines.clear();
	dishTextures.clear();
	ingTextures.clear();
	drawDishes();
}