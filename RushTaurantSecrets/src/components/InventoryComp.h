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
	// vector de 3 platos
	vector<_ecs::_dish_id> dishes;
	// determina si el contenido del vector de platos es válido o no
	vector<bool> dishesBool;
	Texture* texture;
	SDLUtils* sdl;
	InputHandler* ih; //para consultar el input (teclado 123 o mando)
	int dishH, dishW;
	
	int cellSelected; //se encarga de guardar la casilla en la que lleva seleccionada (independientemente de que si tiene que repartir o no)

	// métodos privados
	void renderDish(int xD, int yD, _ecs::_dish_id dishID);
	void setPosition(int i, int& x, int& y);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INVENTORY;
	InventoryComp(GameObject* parent);
	void takeDish(_ecs::_dish_id newDish);
	void freeDish();
	int freeSpace(); //llamado desde fuera
	virtual void render();
	virtual void handleEvents(); //se encarga de comprobar si ha var¨ªado la selecci¨®n de casilla seg¨²n input y se actualiza cellSelected
};

