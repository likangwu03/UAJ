#include "InventoryComp.h"

InventoryComp::InventoryComp(GameObject* parent):Component(parent, id) {
	dishes.reserve(3);
	dishesBool.reserve(3);
	// inicializa el vector de booleanos
	for (int i = 0; i < 3; i++) {
		dishesBool[i] = false;
	}
}

// si hay espacio en el inventario, recoge el plato (suponiendo que previamente ya se ha comprobado si cookingMachine est¨¢ listo en otra clase)
void InventoryComp::takeDish(_ecs::_dish_id newDish) {
	// comprueba que hay espacio libre en el inventario
	int place = freeSpace();
	if (place != -1) {
		dishes[place] = newDish;
		dishesBool[place] = true;
	}
}

// libera el espacio indicado (num) ya sea para tirar el plato, dárselo a un cliente...
void InventoryComp::freeDish(int num) {
	// sólo libera el plato si existe
	// !! pensar en mantener esta implementación o cambiar para sólo seleccionar los huecos cubiertos
	if (dishesBool[num] == true) {
		// si hay más de un plato
		if (num >= 1) {
			for (int i = 0; i < num - 1; i++) {
				dishes[i] = dishes[i + 1];
			}
		}
		dishesBool[num] = false;
	}
}

// devuelve la primera posición libre; si no hay espacio libre, devuelve -1
int InventoryComp::freeSpace() {
	int i = 0;
	bool encontrado = false;
	while (i < 3 && !encontrado) {
		// si hay un hueco libre
		if (dishesBool[i] == false) return i;
		// si no hay un hueco libre
		else i++;
	}

	// devuelve -1 si no tiene ningún hueco libre
	if (i == 3) return -1;
}