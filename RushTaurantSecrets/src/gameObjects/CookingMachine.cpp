
#include "CookingMachine.h"

pair<_ecs::_dish_id, bool> CookingMachine::canFormDish() {
	return dishComb->existDish(ing);
}

void CookingMachine::cook(_ecs::_dish_id d) {
	dish = d;
	state = cooking;
}


void CookingMachine::finishCooking() {
	state = finished;
}

_ecs::_dish_id CookingMachine::pickDish() {
	_ecs::_dish_id dish_aux = dish;
	state = available;
	dish = _ecs::NONE_DISH;
	return dish_aux;
}

bool CookingMachine::isFinished() {
	if (state == 2) return true;
	else return false;
}