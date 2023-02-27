#pragma once
#include "../structure/Component.h"
#include "../structure/Food_def.h"
#include "../components/ClientStateRender.h"
#include <SDL.h>

// Temporal
#include "../sdlutils/InputHandler.h"
using namespace std;
using namespace _ecs;

class ClientState : public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENTSTATE;
	ClientState(GameObject* parent, const vector<_ecs::_dish_id> menu);

	enum States {
		START,    // Caminar hasta mostrador
		ENTRANCE, // Esperar a que le asignen
		ASSIGNED, // Caminar hacia mesa
		THINKING, // Pensando su pedido
		TAKEMYORDER, // Esperando a que le tomen nota
		ORDERED,  // Esperando su pedido
		EATING,   // Comiendo
		FINISH_EAT,	// Ha terminado de comer
		HAS_LEFT,	// Ha dejado la mesa
		REGISTER, // Caminando a la caja
		CASH_REGISTER,	// Ha llegado a la caja
		PAYING,   // Esperando a que le cobren
		OUT       // Saliendo del local
	};

	States getState() const;
	void setState(States state);

	void unHappy() {
		happiness = 0;
	}

private:
	States state;

	const int THINKINGTIME = 5000, EATINGTIME = 5000;
	const float DECREASE = 0.05;
	float happiness, timer, lastTick;

	vector<_ecs::_dish_id> availableDishes;
	ClientStateRender* render;
	_ecs::_dish_id orderedDish;
	bool dishChanged;

public:

	void update();
	void takeOrder();
	_ecs::_dish_id getOrderedDish();
	void getServed();
	void changeDish();
	float getHappiness();

	/*void handleEvents() {
		if (ih().isKeyDown(SDLK_r)) {
			if (state == ORDERED)
				changeDish();
		}
	}*/

};