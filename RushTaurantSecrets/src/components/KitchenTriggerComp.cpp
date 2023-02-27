#include "KitchenTriggerComp.h"

void KitchenTriggerComp::onTriggerExit() {
	ing->removeAllIngredients();
}