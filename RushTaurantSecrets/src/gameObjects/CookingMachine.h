#pragma once

#include <unordered_map>
#include "../structure/Food_def.h"
using namespace std;
class CookingMachine
{
public:
	//determinar si el horno est¨¢ libre, cocinando o que ha cocinado un plato
	enum State{ available,cooking,finished };
	//informar si se puede formar un plato y qu¨¦ plato es
	pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id*>ing);
	//cocinar un plato
	void cook(_ecs::_dish_id* d);
private:
	State state;
	_ecs::_dish_id* dish; // plato que lleva cocinando,null si no hay

};

