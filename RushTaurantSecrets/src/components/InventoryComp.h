#pragma once

#include "../structure/Component.h"
#include "../structure/gameObject.h"
#include "../structure/Food_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include <SDL_rect.h>

class InventoryComp :public Component
{
private:
	// vector de 3 platos
	vector<_ecs::_dish_id> dishes;
	// determina si el contenido del vector de platos es válido o no
	vector<bool> dishesBool;
	Texture* texture;
	SDLUtils* sdl = SDLUtils::instance();
	int dishH, dishW;

	// métodos privados
	void renderDish(int xD, int yD, _ecs::_dish_id dishID);
	void setPosition(int i, int& x, int& y);

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INVENTORY;
	InventoryComp(GameObject* parent);
	void takeDish(_ecs::_dish_id newDish);
	void freeDish(int num);
	int freeSpace();
	virtual void render();
};

