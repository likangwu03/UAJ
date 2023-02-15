#pragma once
#include "../structure/Component.h"
#include "../structure/DishCombinator.h"

class CookingMachineComp:public Component
{
public:
	//determinar si el horno est¨¢ libre, cocinando o que ha cocinado un plato
	enum State { available, cooking, finished };
	constexpr static _ecs::_cmp_id id = _ecs::cmp_COOKMACHINE;
private:
	State state;
	DishCombinator* dishComb; //solo existe uno en todo el juego
	_ecs::_dish_id dish; // plato que lleva cocinando,none si no hay
	//vector<_ecs::_ingredients_id>* ing; //puntero a nube de ingredientes que tiene el jugador

	//ha terminado de cocinar el plato
	void finishCooking();

public:
	CookingMachineComp(GameObject* parent):Component(parent, id),
		state(available), dish(_ecs::_dish_id::NONE_DISH), dishComb(DishCombinator::instance()) {};

	//consultar el plato que tiene
	_ecs::_dish_id getDish() { return dish; }

	//informar si se puede formar un plato y qu¨¦ plato es
	pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id> ing);
	//pair<_ecs::_dish_id, bool> canFormDish(vector<_ecs::_ingredients_id>ing); (VERSION ANTIGUA)

	//cocinar un plato
	void cook(_ecs::_dish_id d);

	//recoger el plato
	_ecs::_dish_id pickDish();

	// informa de si el plato que se est?cocinando ya est?terminado
	// (información para el inventario, para recoger o no el plato)
	bool isFinished();
};

