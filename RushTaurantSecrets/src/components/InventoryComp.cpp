#include "InventoryComp.h"

InventoryComp::InventoryComp(GameObject* parent):Component(parent, id) {
	
	sdl = SDLUtils::instance();
	ih = InputHandler::instance();

	dishes.reserve(3);
	dishesBool.reserve(3);
	// inicializa el vector de booleanos
	for (int i = 0; i < 3; i++) {
		dishesBool.push_back(false);
	}
	for (int i = 0; i < 3; i++) {
		dishes.push_back(_ecs::ALBONDIGAS);
	}
	dishH = 60; dishW = 60;

	cellSelected = -1;

	// prueba--borrar luego
	//dishesBool[0] = true;
	//dishesBool[1] = true;
	//dishesBool[2] = true;
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

// libera el espacio seg¨²n casilla seleccionado previamente ya sea para tirar el plato, dárselo a un cliente...
void InventoryComp::freeDish() {
	// sólo libera el plato si existe
	// !! pensar en mantener esta implementación o cambiar para sólo seleccionar los huecos cubiertos
	if (dishesBool[cellSelected] == true) {
		// si hay más de un plato
		if (cellSelected >= 1) {
			for (int i = 0; i < cellSelected - 1; i++) {
				dishes[i] = dishes[i + 1];
			}
		}
		dishesBool[cellSelected] = false;
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

void InventoryComp::renderDish(int xD, int yD, _ecs::_dish_id dishID) {
	SDL_Rect dest;
	dest.x = xD;
	dest.y = yD;
	dest.w = dishW;
	dest.h = dishH;

	string dID = to_string(dishID);

	// renderiza la textura
	texture = &((*sdl).images().at(dID));
	texture->render(dest);
	
}

void InventoryComp::render() {
	// recorre la lista de platos para renderizarlos
	for (int i = 0; i < 3; i++) {
		// si el plato est?en el inventario, se renderiza
		if (dishesBool[i] == true) {
			int x, y;
			setPosition(i, x, y);
			renderDish(x, y, dishes[i]);
		}
	}
}

void InventoryComp::setPosition(int i, int& x, int& y) {
	if (i == 0) {
		x = 30; y = 482;
	}
	else if (i == 1) {
		x = 30; y = 554;
	}
	else { // i == 2
		x = 30; y = 626;
	}
}

void InventoryComp::setCell(char key) {
	// si no hay ninguna celda seleccionada, selecciona la primera celda libre
	if (cellSelected == -1) freeSpace();
	else {
		// ...
	}
}

void InventoryComp::handleEvents() {
	// flecha izquierda
	if (ih->isKeyDown(SDLK_LEFT))
		setCell('l');
	// flecha derecha
	else if (ih->isKeyDown(SDLK_RIGHT))
		setCell('r');
}