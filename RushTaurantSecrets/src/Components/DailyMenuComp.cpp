#include "DailyMenuComp.h"
#include "../Utilities/checkML.h"

/*
Area donde pueden haber ingredientes: 450, 388 (512)
Cada plato tiene dos filas de 48px para renderizar los platos. 
Se mira el número de ingredientes que tiene el plato, si es > 4 se renderiza en dos filas,
si no, se renderiza en una
*/

void DailyMenuComp::drawDishes()
{
	Vector t = tf->getPos();

	//se dibujan los platos
	for (int i = 0; i < menu->size(); ++i) {
		//textura plato
		Texture* plateTex = &((*SDLUtils::instance()).images().at(std::to_string(menu->at(i).id)));
		float dishx = t.getX() + (dishSpriteSize);
		float dishy = (t.getY() * 4) + (i * (ingredientSpriteSize * 2));
		dishTextures.push_back({ plateTex, dishx, dishy });
		//textura "="
		std::string equalString = ("=");
		Texture* equalTex = new Texture(sdlutils().renderer(), equalString, *font, build_sdlcolor(0x725644FF));
		menuText.push_back({ equalTex, t.getX() + (dishSpriteSize * 1.75f) + fontSize,
			dishy + (dishSpriteSize / 2) });

		int temp = 0;
		int count = 0;
		//se dibujan los ingredientes
		for (auto ing : menu->at(i).ingredients) {
			float ingx = t.getX() + fontSize;
			float ingy = (t.getY() * 4) + (i * (ingredientSpriteSize * 2));
			if (count > 2) {
				temp = 0;
				ingx += (ingredientSpriteSize * 0.75f);
				ingy += ingredientSpriteSize;
			}
			Texture* ingTex = &((*SDLUtils::instance()).images().at(std::to_string(ing)));
			ingTextures.push_back({ ingTex,  ingx + (dishSpriteSize * 2.1f) + (72 * temp),
				ingy + ingOffset});

			std::string plusString = ("+");
			Texture* plusTex = new Texture(sdlutils().renderer(), plusString, *font, build_sdlcolor(0x725644FF));
			menuText.push_back({ plusTex, ingx + (dishSpriteSize * 3.0f) + (64 * temp),
				ingy + (dishSpriteSize / 2) });

			++temp;
			++count;
		}
		//se quita el ultimo +
		menuText.pop_back();

		//se dibuja el precio
		std::string priceString = (std::to_string(menu->at(i).price) + "$");
		Texture* tempTex = new Texture(sdlutils().renderer(), priceString, *font, build_sdlcolor(0xffbb11FF));
		dishTextures.push_back({ tempTex, t.getX() + (dishSpriteSize * 2) + (50 * 5), (t.getY() * 4) + (i * (ingredientSpriteSize * 2)) + 6 });
	}
}

void DailyMenuComp::randomMenu()
{
	//set para evitar que hayan dos platos iguales en el mismo menu
	set<uint8_t> aux;
	vector<_ecs::DishInfo> temp;
	int dish;

	int i = 0;
	//si el jugador ha matado a alguien se a�ade un plato de carne aleatorio
	if (murder) {
		dish = rand() % _ecs::NUM_MEAT_DISH;
		aux.insert(_ecs::MeatDishes[dish].id);
		menu->push_back(_ecs::MeatDishes[dish]);
		++i;
	}
	// Men� del d�a aleatorio (lo rellena con 4 platos diferentes
	// entre s� y los pasa a un vector para poder acceder a ellos)
	// aux sirve para asegurarse de que no se inserta dos veces el mismo plato en el menu

	while (i < menuSize) {
		dish = rand() % _ecs::NUM_DISH;
		if (aux.insert(_ecs::Dishes[dish].id).second) {
			menu->push_back(_ecs::Dishes[dish]);
			i++;
		}
	}
}

void DailyMenuComp::init(GameObject* parent)
{
	tf = parent->getComponent<Transform>();
	parentScene = parent->getScene();

	murder = GameManager::get()->getHasKill();

	font = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	drawDishes();
}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id)
	: Component(parent, id), menuSize(4), dishSpriteSize(64), ingredientSpriteSize(48), 
	ingOffset(8), fontSize(24), random(true)
{
	menu = new vector<_ecs::DishInfo>();
	randomMenu();

	init(parent);
}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, vector<_ecs::DishInfo>* _menu)
	: Component(parent, id), menu(_menu), menuSize(_menu->size()), dishSpriteSize(64), 
	ingOffset(8), ingredientSpriteSize(48), fontSize(24), random(false)
{
	init(parent);
}

DailyMenuComp::~DailyMenuComp()
{
	if(random)
		delete menu;
	delete font;
	for (auto e : menuText) {
		delete e.tex;
	}
}

void DailyMenuComp::render()
{
	for (auto e : dishTextures) {
		e.tex->render(build_sdlrect(e.x, e.y, dishSpriteSize, dishSpriteSize));
	}	
	for (auto i : ingTextures) {
		i.tex->render(build_sdlrect(i.x, i.y, ingredientSpriteSize, ingredientSpriteSize));
	}
	for (auto p : menuText) {
		p.tex->render(build_sdlrect(p.x, p.y, 15, fontSize));
	}
}

vector<_ecs::DishInfo>* DailyMenuComp::getMenu()
{
	return menu;
}

void DailyMenuComp::setMenu(vector<_ecs::DishInfo>* _menu)
{
	menu = _menu;
}
