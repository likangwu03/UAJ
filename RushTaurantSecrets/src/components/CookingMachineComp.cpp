#include "CookingMachineComp.h"

pair<_ecs::_dish_id, bool> CookingMachineComp::canFormDish(vector<_ecs::_ingredients_id> ing) {
	return dishComb->existDish(ing);
}

void CookingMachineComp::cook(_ecs::_dish_id d) {
	dish = d;
	state = cooking;
}


void CookingMachineComp::finishCooking() {
	state = finished;
}

_ecs::_dish_id CookingMachineComp::pickDish() {
	_ecs::_dish_id dish_aux = dish;
	state = available;
	dish = _ecs::NONE_DISH;
	return dish_aux;
}

bool CookingMachineComp::isFinished() {
	if (state == finished) return true;
	else return false;
}