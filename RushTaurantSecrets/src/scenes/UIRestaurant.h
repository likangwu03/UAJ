#pragma once
#include "../scenes/UI.h"
#include "../structure/Food_def.h"
#include "../gameObjects/CookingMachine.h"

// UI del restaurante -- hereda de la clase UI principal
class UIRestaurant : public UI
{
private:
	// vector de 3 ingredientes
	vector<_ecs::_dish_id> dishes[3];
	CookingMachine* cookingMachine;

public:
	UIRestaurant();
	void takeDish(_ecs::_dish_id newDish);
};

