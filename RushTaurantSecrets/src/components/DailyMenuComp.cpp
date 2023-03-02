#include "DailyMenuComp.h"

void DailyMenuComp::drawDishes(vector<_ecs::DishInfo> menu)
{
	Vector t = tf->getPos();

	//se dibujan los platos
	for (int i = 0; i < menu.size(); ++i) {
		GameObject* aux = new GameObject(parentScene, _ecs::grp_HUD, _ecs::hdr_MENU);
		new Transform(aux, Vector(t.getX() + spriteSize, (t.getY() * 4) + (i * spriteSize)), Vector(0, 0), spriteSize, spriteSize, 0);
		new Image(aux, &((*SDLUtils::instance()).images().at(std::to_string(menu[i].id))));
		int temp = 0;
		//se dibujan los ingredientes
		for (auto ing : menu[i].ingredients) {
			GameObject* aux2 = new GameObject(parentScene, _ecs::grp_HUD, _ecs::hdr_MENU);
			new Transform(aux2, Vector(t.getX() + (spriteSize * 2) + (48 * temp), (t.getY() * 4) + (i * spriteSize) + 6), Vector(0, 0), 48, 48, 0);
			new Image(aux2, &((*SDLUtils::instance()).images().at(std::to_string(ing))));
			++temp;
		}
	}
}

vector<_ecs::DishInfo> DailyMenuComp::randomMenu()
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
		temp.push_back(_ecs::MeatDishes[dish]);
		++i;
	}
	// Men� del d�a aleatorio (lo rellena con 4 platos diferentes
	// entre s� y los pasa a un vector para poder acceder a ellos)
	// aux sirve para asegurarse de que no se inserta dos veces el mismo plato en el menu

	while (i < menuSize) {
		dish = rand() % _ecs::NUM_DISH;
		if (aux.insert(_ecs::Dishes[dish].id).second) {
			temp.push_back(_ecs::Dishes[dish]);
			i++;
		}
	}

	return temp;
}

DailyMenuComp::DailyMenuComp(GameObject* parent, float w, float h, _ecs::_cmp_id id, uint8_t mSize, bool m)
	: Component(parent, id), menuSize(mSize), spriteSize(64), murder(m)
{
	tf = parent->getComponent<Transform>();
	parentScene = parent->getScene();

	drawDishes(randomMenu());
}
