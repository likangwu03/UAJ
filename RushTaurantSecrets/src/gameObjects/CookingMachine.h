#pragma once

#include "../structure/DishCombinator.h"
using namespace std;
class CookingMachine
{
public:
	//determinar si el horno est¨¢ libre, cocinando o que ha cocinado un plato
	enum State { available, cooking, finished };
private:
	State state;
	DishCombinator* dishComb; //solo existe uno en todo el juego
	_ecs::_dish_id dish; // plato que lleva cocinando,none si no hay
	vector<_ecs::_ingredients_id>* ing; //puntero a nube de ingredientes que tiene el jugador

	//ha terminado de cocinar el plato
	void finishCooking();

public:
	CookingMachine(DishCombinator* _dishComb, vector<_ecs::_ingredients_id>* _ing) :
		state(available), dish(_ecs::_dish_id::NONE_DISH), ing(_ing), dishComb(_dishComb) {};

	//consultar el plato que tiene
	_ecs::_dish_id getDish() { return dish; }

	//informar si se puede formar un plato y qu¨¦ plato es
	pair<_ecs::_dish_id, bool> canFormDish();
	//pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id>ing); (VERSION ANTIGUA)

	//cocinar un plato
	void cook(_ecs::_dish_id d);

	//recoger el plato
	_ecs::_dish_id pickDish();

};

