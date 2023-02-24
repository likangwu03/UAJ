#include "DailyMenu.h"
//cambiar a market
#include "SuperMarket.h"
#include "../structure/SceneManager.h"

vector<_ecs::DishInfo> DailyMenu::randomMenu()
{
	//set para evitar que hayan dos platos iguales en el mismo menu
	set<uint8_t> aux;
	vector<_ecs::DishInfo> temp;
	int t;
	int i = 0;

	//si el jugador ha matado a alguien se añade un plato de carne aleatorio
	if (murder) {
		t = rand() % _ecs::NUM_MEAT_DISH;
		aux.insert(_ecs::MeatDishes[t].id);
		temp.push_back(_ecs::MeatDishes[t]);
		++i;
	}
	// Menú del día aleatorio (lo rellena con 4 platos diferentes
	// entre sí y los pasa a un vector para poder acceder a ellos)
	// aux sirve para asegurarse de que no se inserta dos veces el mismo plato en el menu
	for (; i < menuSize; i++) {
		t = rand() % _ecs::NUM_DISH;
		if (aux.insert(_ecs::Dishes[t].id).second) {
			temp.push_back(_ecs::Dishes[t]);
		}
		else --i;
	}

	return temp;
}

void DailyMenu::drawDishes(GameObject* d, vector<_ecs::DishInfo> menu)
{
	Vector t = d->getComponent<Transform>()->getPos();

	//se dibujan los platos
	for (int i = 0; i < menu.size(); ++i) {
		GameObject* aux = new GameObject(this, _ecs::grp_HUD, _ecs::hdr_MENU);
		new Transform(aux, Vector(t.getX() + spriteSize, (t.getY() * 4) + (i * spriteSize)), Vector(0, 0), spriteSize, spriteSize, 0);
		new Image(aux, &((*sdl).images().at(std::to_string(menu[i].id))));
		int temp = 0;
		//se dibujan los ingredientes
		for (auto ing : menu[i].ingredients) {
			GameObject* aux2 = new GameObject(this, _ecs::grp_HUD, _ecs::hdr_MENU);
			new Transform(aux2, Vector(t.getX() + (spriteSize * 2) + (48 * temp), (t.getY() * 4) + (i * spriteSize) + 6), Vector(0, 0), 48, 48, 0);
			new Image(aux2, &((*sdl).images().at(std::to_string(ing))));
			++temp;
		}
	}
}

void DailyMenu::select(SceneManager* sceneManager)
{
	sceneManager->ChangeScene(SceneManager::SUPERMARKET);
}

DailyMenu::DailyMenu(SceneManager* sceneManager, uint8_t msize, bool m) : murder(m), menuSize(msize), spriteSize(64)
{
	//dest = { (1280 / 2) - (BUTTON_W * 4 / 2), 400, BUTTON_W * 4, BUTTON_H * 4 };

	GameObject* dailyMenu1 = new GameObject(this, _ecs::grp_HUD, _ecs::hdr_MENU);
	new Transform(dailyMenu1, Vector(sdl->width() / 8, sdl->height() / 15), Vector(0, 0), 451, 603, 0);
	new Image(dailyMenu1, &((*sdl).images().at("DAILY_MENU")));

	GameObject* dailyMenu2 = new GameObject(this, _ecs::grp_HUD, _ecs::hdr_MENU);
	new Transform(dailyMenu2, Vector(sdl->width() / 2, sdl->height() / 15), Vector(0, 0), 451, 603, 0);
	new Image(dailyMenu2, &((*sdl).images().at("DAILY_MENU")));

	menu1 = randomMenu();
	menu2 = randomMenu();

	drawDishes(dailyMenu1, menu1);
	drawDishes(dailyMenu2, menu2);

	//new Button(dailyMenu1, sceneManager, select);
	//new Button(dailyMenu2, sceneManager, select);
}

void DailyMenu::handleEvents() {
	int x, y;		// corrdenadas del puntero del ratón
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 1, 1 };



	//if (SDL_HasIntersection(&mouseRect, &dest)) {
	//	frame = 1;
	//	if (InputHandler::instance()->getMouseButtonState(InputHandler::instance()->LEFT)) {
	//		callback(sceneManager);
	//	}
	//}
	//else if (InputHandler::instance()->joysticksInitialised()) {
	//	if (InputHandler::instance()->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
	//		frame = 1;
	//		InputHandler::instance()->clean();
	//		callback(sceneManager);
	//	}
	//}
	//else frame = 0;
}
