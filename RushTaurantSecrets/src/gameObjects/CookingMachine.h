#pragma once
#include "Dish.h"
#include "Ingredient.h"
#include <unordered_map>
using namespace std;
class CookingMachine
{
public:
	//determinar si el horno est¨¢ libre, cocinando o que ha cocinado un plato
	enum State{ available,cooking,finished };
	//informar si se puede formar un plato y qu¨¦ plato es
	pair<Dish*, bool> canFormDish(vector<Ingredient*>ing);
	//cocinar un plato
	void cook(Dish* d);
private:
	State state;
	Dish* dish; // plato que lleva cocinando,null si no hay

};

