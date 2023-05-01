#include "CookingMachineTrigger.h"
#include "../Utilities/checkML.h"
#include "../Structure/Game.h"

void CookingMachineTrigger::isOverlapping() {
	float auxPos = p->getPos().getX() + p->getW() / 2;
	if (p->getOrientation() != north || auxPos < transform_->getPos().getX() ||auxPos >transform_->getPos().getX() + width) {
		highlight->setActive(false); return;
	}
	highlight->setActive(true);
	if (ih->joysticksInitialised()) {
		if (!ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) return;
	}
	else if (!ih->isKeyDown(SDLK_SPACE)) return;

	CookingMachineComp::State state = cook->getState();
	pair<_ecs::_dish_id, bool>aux;
	switch (state) {
	case CookingMachineComp::available:

		aux = cook->canFormDish(other_->getComponent<Ingredients>()->getIngredients());
		if (aux.second) {
			cook->cook(aux.first); // cocina si se puede formar un plato
			other_->getComponent<Ingredients>()->cookingIngredients();

			Message m;
			m.id = Message::msg_COOKING_DISH;
			m.cooking_machine.id = cook->getNum();
			m.cooking_machine.dish = aux.first;
			Game::get()->getCoopHandler()->send(m);
		}
		else cook->informCannotCook();
		break;
	case CookingMachineComp::cooking: //no hace nada
		break;
	case CookingMachineComp::finished:
		if (!inventory->isFull()) {
			Message m2;
			m2.id = Message::msg_PICK_DISH;
			m2.cooking_machine.id = cook->getNum();
			m2.cooking_machine.dish = 0;
			Game::get()->getCoopHandler()->send(m2);
			inventory->takeDish(cook->pickDish());
		}
		break;
	}
}
void CookingMachineTrigger::onTriggerExit() {
	highlight->setActive(false); return;
}