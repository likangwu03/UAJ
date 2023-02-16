#include "CookingMachineCol.h"

void CookingMachineCol::collision(Player* p) {
	CookingMachineComp::State s = cook->getState();
	pair<_ecs::_dish_id, bool>aux;
	switch (s){
	case CookingMachineComp::available:
		aux = cook->canFormDish(p->getComponent<Ingredients>()->getIngredients());
		if (aux.second) cook->cook(aux.first); // cocina si se puede formar un plato
		else cout << "cookingMachineCol: no se puede formarse un plato" << endl;
		break;
	case CookingMachineComp::cooking: //no hace nada
		break;
	case CookingMachineComp::finished:
		//p-> cook->getDish();
		break;
	}
}