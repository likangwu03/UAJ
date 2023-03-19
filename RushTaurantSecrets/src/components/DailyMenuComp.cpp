#include "DailyMenuComp.h"
#include "../utils/checkML.h"

void DailyMenuComp::drawDishes()
{
	Vector t = tf->getPos();

	//se dibujan los platos
	for (int i = 0; i < menu->size(); ++i) {
		//se dibujan los platos
		for (int i = 0; i < menu->size(); ++i) {
			Texture* plateTex = &((*SDLUtils::instance()).images().at(std::to_string(menu->at(i).id)));
			textures.push_back({ plateTex, t.getX() + (spriteSize), (t.getY() * 4) + (i * spriteSize) });
			//plateTex->render(t.getX() + (spriteSize), (t.getY() * 4) + (i * spriteSize));
			int temp = 0;
			//se dibujan los ingredientes
			for (auto ing : menu->at(i).ingredients) {
				Texture* ingTex = &((*SDLUtils::instance()).images().at(std::to_string(ing)));
				textures.push_back({ ingTex, t.getX() + (spriteSize * 2) + (48 * temp), (t.getY() * 4) + (i * spriteSize) + 6 });
				//ingTex->render(t.getX() + (spriteSize * 2) + (48 * temp), (t.getY() * 4) + (i * spriteSize) + 6);
				++temp;
			}
			//se dibuja el precio
			/*GameObject* price = new GameObject(parentScene, _ecs::grp_HUD, _ecs::hdr_MENU);
			new Transform(price, Vector(t.getX() + (spriteSize * 2) + (50 * 5), (t.getY() * 4) + (i * spriteSize) + 6), Vector(0, 0), 48, 48, 0);*/
			std::string priceString = (std::to_string(menu->at(i).price) + "$");
			Texture* tempTex = new Texture(sdlutils().renderer(), priceString, *font, build_sdlcolor(0xffbb11FF));
			prices.push_back({ tempTex, t.getX() + (spriteSize * 2) + (50 * 5), (t.getY() * 4) + (i * spriteSize) + 6 });
			//tempTex->render(t.getX() + (spriteSize * 2) + (50 * 5), (t.getY() * 4) + (i * spriteSize) + 6);
		}
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

	murder = GameManager::instance()->getHasKill();

	font = new Font("assets/Fonts/light_pixel-7.ttf", 50);
	drawDishes();
}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, uint8_t mSize)
	: Component(parent, id), menuSize(mSize), spriteSize(64)
{
	menu = new vector<_ecs::DishInfo>();
	randomMenu();

	init(parent);
}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, vector<_ecs::DishInfo>* _menu)
	: Component(parent, id), menu(_menu), menuSize(_menu->size()), spriteSize(64)
{
	init(parent);
}

DailyMenuComp::~DailyMenuComp()
{
	//delete menu;
	delete font;
	for (auto e : prices) {
		delete e.tex;
	}
}

void DailyMenuComp::render()
{
	for (auto e : textures) {
		e.tex->render(build_sdlrect(e.x, e.y, spriteSize, spriteSize));
	}
	for (auto p : prices) {
		p.tex->render(build_sdlrect(p.x, p.y, spriteSize, spriteSize));
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
