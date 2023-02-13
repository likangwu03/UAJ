#include "Inventory.h"

//Inventory* Inventory::_instance = nullptr;

Inventory::Inventory(CookingMachine* cM) : cookingMachine(cM) {
	dishes.reserve(3);
	dishesBool.reserve(3);
	// inicializa el vector de booleanos
	for (int i = 0; i < 3; i++) {
		dishesBool[i] = false;
	}
}

// si la CookingMachine ha terminado (y hay espacio en el inventario), recoge el plato
void Inventory::takeDish(_ecs::_dish_id newDish) {
	// comprueba que la cooking machine ha terminado
	if (cookingMachine->isFinished()) {
		// comprueba que hay espacio libre en el inventario
		int place = freeSpace();
		if (place != -1) {
			dishes[place] = newDish;
			dishesBool[place] = true;
		}
	}
}

// libera el espacio indicado (num) ya sea para tirar el plato, d�rselo a un cliente...
void Inventory::freeDish(int num) {
	// s�lo libera el plato si existe
	// !! pensar en mantener esta implementaci�n o cambiar para s�lo seleccionar los huecos cubiertos
	if (dishesBool[num] == true) {
		// si hay m�s de un plato
		if (num >= 1) {
			for (int i = 0; i < num - 1; i++) {
				dishes[i] = dishes[i + 1];
			}
		}
		dishesBool[num] = false;
	}
}

// devuelve la primera posici�n libre; si no hay espacio libre, devuelve -1
int Inventory::freeSpace() {
	int i = 0;
	bool encontrado = false;
	while (i < 3 && !encontrado) {
		// si hay un hueco libre
		if (dishesBool[i] == false) return i;
		// si no hay un hueco libre
		else i++;
	}

	// devuelve -1 si no tiene ning�n hueco libre
	if (i == 3) return -1;
}