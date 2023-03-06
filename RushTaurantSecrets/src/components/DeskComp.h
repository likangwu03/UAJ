#pragma once
#include "../structure/Component.h"
#include "TriggerComp.h"
#include <vector>
class Transform;
class Client;

class DeskComp : public TriggerComp {
private:
	Transform* trans;
	std::vector<Client*> assigned;
	bool sucia;
	int num;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_DESK;

	DeskComp(GameObject* parent, float width, float height, int id);

	int getID() { return num; }

	void assignClients(const std::vector<Client*>& clients);

	// Se pasa como parámetro el plato que se quiera servir a los clientes asignados a la mesa.
	// Devuelve true si un cliente ha recibido el plato que quería,
	// o false si nadie ha aceptado el plato (no lo pedían o ya lo han recibido) 
	void spreadOverlap();

	// Se llama cuando los clientes se van de la mesa.
	void leaveDesk();

	// Se llama cuando se quiere limpiar la mesa.
	void cleanDesk();

	bool isOccupied();

	void isOverlapping() override;

	void update();
};