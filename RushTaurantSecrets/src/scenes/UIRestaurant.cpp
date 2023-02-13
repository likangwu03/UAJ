#include "UIRestaurant.h"

UIRestaurant::UIRestaurant() : UI() {
	// se añaden los iconos a la lista de gameObjects
	// icono de diana (objetivo diario)
	// CAMBIAR POSICIÓN DEFINITIVA
	objects.push_back(new Icon(this, 10, 50, texturesUI[4]));
	// icono de reputación (anterior a las estrellitas)
	// CAMBIAR POSICIÓN DEFINITIVA 
	objects.push_back(new Icon(this, 10, 50, texturesUI[5]));
	// TO-DO ESTRELLITAS
	// inventario de platos cocinados (tres espacios)
	// CAMBIAR POSICIÓN DEFINITIVA 
	objects.push_back(new Icon(this, 10, 50, texturesUI[6]));

}
