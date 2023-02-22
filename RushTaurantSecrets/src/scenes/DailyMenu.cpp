#include "DailyMenu.h"
//cambiar a market
#include "Restaurant.h"
#include "../structure/SceneManager.h"

vector<_ecs::DishInfo> DailyMenu::randomMenu()
{
	// Menú del día aleatorio (lo rellena con 4 platos diferentes
	// entre sí y los pasa a un vector para poder acceder a ellos)
	// aux sirve para asegurarse de que no se inserta dos veces el mismo plato en el menu
	set<_ecs::DishInfo> aux;
	vector<_ecs::DishInfo> temp;
	int t;

	//si el jugador ha matado a alguien se añade un plato de carne aleatorio
	if (murder) {
		t = rand() % _ecs::NUM_MEAT_DISH;
		aux.insert(_ecs::Dishes[t]);
		temp.push_back(_ecs::Dishes[t]);
	}
	for (int i = 0; i < 4; i++) {
		t = rand() % _ecs::NUM_DISH;
		if (aux.insert(_ecs::Dishes[t]).second) {
			temp.push_back(_ecs::Dishes[t]);
		}
		else --i;
	}

	return temp;
}

DailyMenu::DailyMenu(bool m = false) : murder(m), market(nullptr)
{
	// icono de menú del día
	GameObject* dailyMenuBG = new GameObject(this, _ecs::grp_HUD, _ecs::hdr_MENU);
	new Transform(dailyMenuBG, Vector(sdl->width() / 2, sdl->height() / 2), Vector(0, 0), 50, 50, 0);
	new Image(dailyMenuBG, &((*sdl).images().at("DIALOG_BOX")));

	menu1 = randomMenu();
	menu2 = randomMenu();
}

void DailyMenu::linkSupermarket(Restaurant* sm)
{
	this->market = sm;
}
