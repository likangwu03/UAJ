#pragma once
#include "../structure/Component.h"

class ClientState : public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENTSTATE;
	ClientState(GameObject* parent) : Component(parent, id), state(START) { }

	enum States {
		START,    // Caminar hasta mostrador
		ENTRANCE, // Esperar a que le asignen
		ASSIGNED, // Caminar hacia mesa
		THINKING, // Pensando su pedido
		TAKEMYORDER, // Esperando a que le tomen nota
		ORDERED, // Esperando su pedido
		EATING,   // Comiendo
		REGISTER, // Caminando a la caja
		PAYING,   // Esperando a que le cobren
		OUT       // Saliendo del local
	};

	States getState() const { return state; }
	void setState(States state) { this->state = state; }

private:
	States state;
};