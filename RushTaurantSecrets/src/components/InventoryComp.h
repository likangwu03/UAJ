#pragma once

#include "../structure/Component.h"
#include "../structure/gameObject.h"
#include "../structure/Food_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include <SDL_rect.h>

class InventoryComp :public Component
{
private:
	const int MAX_DISHES = 3;
	const int DISHX = 36, DISHY = 413, DISHOFFSET = 72;
	// vector de 3 platos
	vector<_ecs::_dish_id> dishes;
	// determina si el contenido del vector de platos es válido o no
	vector<bool> dishesBool;
	Texture* texture;
	SDLUtils* sdl;
	InputHandler* ih; //para consultar el input (teclado 123 o mando)
	const int DISH_SIZE = 50;
	int cellsOcuppied;
	int cellSelected; //se encarga de guardar la casilla en la que lleva seleccionada (independientemente de que si tiene que repartir o no)

	// métodos privados
	void renderDish(int xD, int yD, _ecs::_dish_id dishID);
	void setPosition(int i, int& x, int& y);
	int firstDishL(int num);
	int firstDishR(int num);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INVENTORY;
	InventoryComp(GameObject* parent);
	void takeDish(_ecs::_dish_id newDish);
	void freeDish();
	bool isFull() { return cellsOcuppied == MAX_DISHES; } //indica si el inventario est¨¢ lleno
	int freeSpace(); //llamado desde fuera
	virtual void render();
	virtual void handleEvents(); //se encarga de comprobar si ha var¨ªado la selecci¨®n de casilla seg¨²n input y se actualiza cellSelected
	void setCell(SDL_KeyCode key);
};

