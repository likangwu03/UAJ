#pragma once

#include "../structure/Component.h"
#include "../structure/Food_def.h"

class InventoryComp :public Component
{
private:
	// vector de 3 ingredientes
	vector<_ecs::_dish_id> dishes;
	// determina si el contenido del vector de platos es válido o no
	vector<bool> dishesBool;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_INVENTORY;
	InventoryComp(GameObject* parent);
	void takeDish(_ecs::_dish_id newDish);
	void freeDish(int num);
	int freeSpace();
};

