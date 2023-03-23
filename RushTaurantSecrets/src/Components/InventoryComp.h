#pragma once

#include "../Structure/Component.h"
#include "../Structure/gameObject.h"
#include "../Definitions/Food_def.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/InputHandler.h"
#include <SDL_rect.h>

class InventoryComp :public Component
{
private:
	const int MAX_DISHES = 4;
	const int DISHX = 36, DISHY = 413, DISHOFFSET = 72,
			  HIGHLIGHT_X = 26, HIGHLIGHT_Y = 405, HIGHLIGHTSIZE = 70;

	// vector de 3 platos
	vector<_ecs::_dish_id> dishes;
	// determina si el contenido del vector de platos es válido o no
	vector<bool> dishesBool;
	Texture* texture;
	Texture* highlight;
	SDLUtils* sdl;
	InputHandler* ih; //para consultar el input (teclado 123 o mando)
	const int DISH_SIZE = 50;
	int cellsOcuppied;
	int cellSelected; //se encarga de guardar la casilla en la que lleva seleccionada (independientemente de que si tiene que repartir o no)

	// métodos privados
	void renderDish(int xD, int yD, _ecs::_dish_id dishID);
	void setPosition(int i, int& x, int& y);
	void prevDish();
	void nextDish();

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INVENTORY;
	InventoryComp(GameObject* parent);
	void takeDish(_ecs::_dish_id newDish);
	void freeDish();
	bool isFull() { return cellsOcuppied == MAX_DISHES; } //indica si el inventario está lleno
	int freeSpace(); //llamado desde fuera
	bool serveDish(_ecs::_dish_id dish);

	virtual void render();
	virtual void handleEvents(); //se encarga de comprobar si ha var¨ªado la selecci¨®n de casilla seg¨²n input y se actualiza cellSelected
};

