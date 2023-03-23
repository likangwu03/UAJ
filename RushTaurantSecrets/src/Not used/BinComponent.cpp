#include "BinComponent.h"

#include "../utils/checkML.h"

BinComponent::BinComponent(GameObject* parent, Vector pos) : Component(parent, id), myParent(parent) {
	// puntero al inventario del jugador
	// !! ¿posible problema con que la papelera esté en la escena Restaurant y el inventario esté en la escena UIRestaurant?
	//myInventory = myParent->getScene()->getGameObject(hdr_INVENTORY)->getComponent<InventoryComp>();
}

void BinComponent::handleEvents() {
	// gestión de interacción aquí
	// ...
	// tecla de prueba
	//if (ih->isKeyDown(SDLK_1))
		//myInventory->freeDish();

}