#include "Inventory.h"

//Inventory* Inventory::_instance = nullptr;

// si la CookingMachine ha terminado (y hay espacio en el inventario), recoge el plato
void Inventory::takeDish(_ecs::_dish_id newDish) {
	if (cookingMachine->isFinished()) dishes->push_back(newDish);
}

// libera el espacio indicado (num) ya sea para tirar el plato, dárselo a un cliente...
void Inventory::freeDish(int num) {
	if (!dishes[num].empty()) {
		// TO-DO borrar primera posición 
		for (int i = num; i < 2; i++) {
			if (!dishes[i + 1].empty()) { // si hay un plato en ese espacio
				dishes[i] = dishes[i + 1];
			}
		}
		// if (!dishes[2].empty()) // TO-DO borrar última posición 
	}
}