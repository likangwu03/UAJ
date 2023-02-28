#include "InventoryComp.h"

#include "../utils/checkML.h"

InventoryComp::InventoryComp(GameObject* parent):Component(parent, id) {
	
	sdl = SDLUtils::instance();
	ih = InputHandler::instance();

	dishes.reserve(MAX_DISHES);
	dishesBool.reserve(MAX_DISHES);
	// inicializa el vector de booleanos
	for (int i = 0; i < MAX_DISHES; i++) { // cleon: este "3", casi seguro que es una constante de juego (idealmente, un par�metro) -> Arreglado
		dishesBool.push_back(false);
	}
	for (int i = 0; i < MAX_DISHES; i++) {
		dishes.push_back(_ecs::ALBONDIGAS);
	}

	cellSelected = -1;
	cellsOcuppied = 0;
	// prueba--borrar luego
	/*dishesBool[0] = true;
	dishesBool[1] = true;
	cellsOcuppied = 2;
	dishesBool[2] = true;*/
}

// si hay espacio en el inventario, recoge el plato (suponiendo que previamente ya se ha comprobado si cookingMachine est�� listo en otra clase)
void InventoryComp::takeDish(_ecs::_dish_id newDish) {
	// comprueba que hay espacio libre en el inventario
	int place = freeSpace();
	if (place != -1) {
		dishes[place] = newDish;
		dishesBool[place] = true;
		++cellsOcuppied;
		cellSelected = place;
	}
}

// libera el espacio seg��n casilla seleccionado previamente ya sea para tirar el plato, d�rselo a un cliente...
void InventoryComp::freeDish() {
	dishesBool[cellSelected] = false;
	firstDishR(cellSelected);
	--cellsOcuppied;
}

// devuelve la primera posici�n libre; si no hay espacio libre, devuelve -1
int InventoryComp::freeSpace() {
	int i = 0;
	bool encontrado = false;
	while (i < MAX_DISHES && !encontrado) { // cleon: s�per 3. -> Arreglado
		// si hay un hueco libre
		if (dishesBool[i] == false) return i;
		// si no hay un hueco libre
		else i++;
	}

	// devuelve -1 si no tiene ning�n hueco libre
	if (i == MAX_DISHES) return -1;
}

void InventoryComp::renderDish(int xD, int yD, _ecs::_dish_id dishID) {
	SDL_Rect dest;
	dest.x = xD;
	dest.y = yD;
	dest.w = DISH_W;
	dest.h = DISH_H;

	string dID = to_string(dishID);

	// renderiza la textura
	texture = &((*sdl).images().at(dID));
	texture->render(dest);
	
}

void InventoryComp::render() {
	// recorre la lista de platos para renderizarlos
	for (int i = 0; i < MAX_DISHES; i++) { // cleon: Super 3 is back -> Arreglado
		// si el plato est?en el inventario, se renderiza
		if (dishesBool[i] == true) {
			int x, y;
			setPosition(i, x, y);
			renderDish(x, y, dishes[i]);
		}
	}
}

void InventoryComp::setPosition(int i, int& x, int& y) {

	// cleon: no puedo a�adir nada a esto. es simplemente bello.
	// cleon: e inexplicable.
	x = 35;
	if (i == 0)  y = 490;
	else if (i == 1) y = 560;
	else /* if (i == 2) */ y = 630;
	
}

void InventoryComp::setCell(char key) { // cleon: SDL_KEY
	// si no hay ninguna celda seleccionada, selecciona la primera celda libre
	if (cellSelected == -1) freeSpace();
	else {
		// si se ha pulsado la tecla izquierda
		if (key == 'l') cellSelected = firstDishL(cellSelected);// cleon: SDL_KEY
		// si se ha pulsado la tecla derecha
		else if (key == 'r') cellSelected = firstDishR(cellSelected);// cleon: SDL_KEY
	}
}

void InventoryComp::handleEvents() {
	// flecha izquierda
	if (ih->isKeyDown(SDLK_LEFT))
		setCell('l');// cleon: SDL_KEY
	// flecha derecha
	else if (ih->isKeyDown(SDLK_RIGHT))
		setCell('r');// cleon: SDL_KEY
}

// busca la siguiente posici�n ocupada en el inventario a la izquierda de la casilla seleccionada
int InventoryComp::firstDishL(int num) {
	int i = 0;
	int n = num;
	while (i < MAX_DISHES) { // super 3: love and thunder.
		// si el �ndice del inventario es 0
		if (n == 0) n = 2; // cleon: super 3 contra super 2: la batalla final.
		else n--;

		if (dishesBool[n] == true) return true; // cleon: m�sica. armon�a. PAZ. Te perdonamos. Don't do it again.
		++i;
	}
	return num;
}

// busca la siguiente posici�n ocupada en el inventario a la derecha de la casilla seleccionada
int InventoryComp::firstDishR(int num) {
	int i = 0;
	int n = num;
	while (i < MAX_DISHES) {
		// si el �ndice del inventario es 0
		if (n == 2) n = 0;
		else n++;

		if (dishesBool[n] == true) return true; // cleon: ugh.
		++i;
	}
	return num;
}