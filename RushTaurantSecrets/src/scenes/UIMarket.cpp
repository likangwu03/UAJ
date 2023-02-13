#include "UIMarket.h"

UIMarket::UIMarket() : UI() {
	// se añaden los iconos a la lista de gameObjects
	// icono de cesta
	objects.push_back(new Icon(this, 10, 50, texturesUI[3]));
	// TO-DO CESTA DESPLEGABLE
}