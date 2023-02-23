#include "CookingMachineTrigger.h"

#include "../utils/checkML.h"

void CookingMachineTrigger::isOverlapping() {
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
	}	
	else if (!ih->isKeyDown(SDLK_SPACE)) return;

	CookingMachineComp::State s = cook->getState();
	pair<_ecs::_dish_id, bool>aux;
	switch (s) {
	case CookingMachineComp::available:
	
		aux = cook->canFormDish(other_->getComponent<Ingredients>()->getIngredients());
		if (aux.second) {
			cook->cook(aux.first); // cocina si se puede formar un plato
			other_->getComponent<Ingredients>()->removeAllIngredients();
		}
		else cout << "cookingMachineCol: no se puede formarse un plato" << endl;
		break;
	case CookingMachineComp::cooking: //no hace nada
		break;
	case CookingMachineComp::finished:
		if (!inventory->isFull())
			inventory->takeDish(cook->pickDish());
		break;
	}
}