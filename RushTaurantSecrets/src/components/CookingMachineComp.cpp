#include "CookingMachineComp.h"
#include "../structure/GameObject.h"
CookingMachineComp::CookingMachineComp(GameObject* _parent) :Component(_parent, id),
state(available), dish(_ecs::_dish_id::NONE_DISH), cont(0), cookingTime(0), 
transform(parent->getComponent<Transform>()),anim(parent->getComponent<UIAnimator>()),
dishComb(DishCombinator::instance()), sdl(SDLUtils::instance())
{
	textures.bubble = &((*sdl).images().at("BUBBLE_ICON"));
	renderPos = transform->getPos();
	anim->setActive(false); 
};
pair<_ecs::_dish_id, bool> CookingMachineComp::canFormDish(vector<_ecs::_ingredients_id> ing) {
	return dishComb->existDish(ing);
}

void CookingMachineComp::cook(_ecs::_dish_id d) {
	dish = d;
	cookingTime = _ecs::Dishes[d].cookingTime;
	cont = sdl->currRealTime();
	state = cooking;
	anim->setActive(true);
}

void CookingMachineComp::finishCooking() {
	state = finished;
	anim->setActive(false);
	textures.dishTex = &((*sdl).images().at(to_string(dish)));

}

_ecs::_dish_id CookingMachineComp::pickDish() {
	_ecs::_dish_id dish_aux = dish;
	state = available;
	dish = _ecs::NONE_DISH;
	
	return dish_aux;
}

void CookingMachineComp::update() {
	if (state == cooking && sdl->currRealTime() - cont >= cookingTime * 1000) {
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
		SDL_Rect dest;
		dest.x = renderPos.getX() + BUBBLE_OFFSETX;
		dest.y = renderPos.getY() + BUBBLE_OFFSETY;
		dest.w = BUBBLE_WIDTH;
		dest.h = BUBBLE_HEIGHT;
		textures.bubble->render(dest);
		//dish
		if (dish != _ecs::NONE_DISH) {
			dest.x = (dest.x+ BUBBLE_WIDTH/2) - DISH_WIDTH/2+DISH_OFFSETX;
			dest.y = dest.y + BUBBLE_HEIGHT / 2 - DISH_HEIGHT / 2 + DISH_OFFSETX;
			dest.w = DISH_WIDTH;
			dest.h = DISH_HEIGHT;
			textures.dishTex->render(dest);
		}
		break;
	}
}