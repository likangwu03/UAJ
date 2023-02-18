#include "CashRegisterTrigger.h"

void CashRegisterTrigger::isOverlapping() {
	if (other_->getComponent<PlayerMovementController>() == nullptr)return; //si no es el jugador, no hace nada
	if (!ih->isKeyDown(SDLK_SPACE)) return; //si no ha interactuado, no hace nada
	
	//si se detecta que hay clientes en la caja
	// coge el dinero del cliente y lo pasa al contador de diner
	money->addMoney(_ecs::Dishes[clientManager->client->getOrderedDish()].price);
	//informa al cliente de que ya puede irse
}