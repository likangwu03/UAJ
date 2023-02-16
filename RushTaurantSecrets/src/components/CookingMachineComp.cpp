#include "CookingMachineComp.h"
CookingMachineComp::CookingMachineComp(GameObject* parent,Vector pos) :Component(parent, id),renderPos(pos),
state(available), dish(_ecs::_dish_id::NONE_DISH), dishComb(DishCombinator::instance()), sdl(SDLUtils::instance()), cont(0)
{
	textures.bubble= &((*sdl).images().at("BUBBLE_ICON"));
	//textures.cookingTex= &((*sdl).images().at("BUBBLE_ICON"));
};
pair<_ecs::_dish_id, bool> CookingMachineComp::canFormDish(vector<_ecs::_ingredients_id> ing) {
	return dishComb->existDish(ing);
}

void CookingMachineComp::cook(_ecs::_dish_id d) {
	dish = d;
	cookingTime = _ecs::Dishes[d].cookingTime;
	cont = sdl->currRealTime();
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

void CookingMachineComp::update(){
	if (state == cooking && sdl->currRealTime() - cont >= cookingTime*1000) {
		finishCooking();
	}
}

void CookingMachineComp::render() {
	switch (state)
	{
	case CookingMachineComp::available: //de momento no hace nada
		break;
	case CookingMachineComp::cooking: //puntos suspensivos
		break;
	case CookingMachineComp::finished:
		//textures.bubble->render()
			break;
	}
}