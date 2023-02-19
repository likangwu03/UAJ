#pragma once
#include "../structure/Component.h"
#include "../structure/Food_def.h"
#include <SDL.h>

// Temporal
#include "../sdlutils/InputHandler.h"
using namespace std;

class ClientState : public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENTSTATE;
	ClientState(GameObject* parent, const vector<_ecs::_dish_id> menu) : Component(parent, id), 
		state(START), happiness(100), timer(0), lastTick(SDL_GetTicks()), availableDishes(menu), orderedDish(-1), dishChanged(false) { }

	enum States {
		START,    // Caminar hasta mostrador
		ENTRANCE, // Esperar a que le asignen
		ASSIGNED, // Caminar hacia mesa
		THINKING, // Pensando su pedido
		TAKEMYORDER, // Esperando a que le tomen nota
		ORDERED,  // Esperando su pedido
		EATING,   // Comiendo
		FINISH_EAT,	// Ha terminado de comer
		REGISTER, // Caminando a la caja
		CASH_REGISTER,	// Ha llegado a la caja
		PAYING,   // Esperando a que le cobren
		OUT       // Saliendo del local
	};

	States getState() const { return state; }
	void setState(States state) { this->state = state; }

private:
	States state;

	const int THINKINGTIME = 5000, EATINGTIME = 5000;
	const float DECREASE = 0.05;
	float happiness, timer, lastTick;

	vector<_ecs::_dish_id> availableDishes;
	int orderedDish;
	bool dishChanged;

public:

	void update() {
		// Si está en estados en los que el jugador tenga que interactuar con él, va bajando la felicidad poco a poco
		if (state == ENTRANCE || state == TAKEMYORDER || state == ORDERED || state == PAYING) {
			happiness -= DECREASE;

			// Si la felicidad llega a 0, se pone el estado a OUT
			// (DE MOMENTO TARDA COMO 1 MINUTO)
			if (happiness <= 0) {
				state = OUT;
			#ifdef _DEBUG
				cout << "Happiness reached 0, leaving restaurant" << endl;
			#endif
			}
		}
		// Si no, si está pensando o comiendo, se actualiza el temporizador de lo que tarda en realizar la acción
		else if (state == THINKING || state == EATING) {
			int delta = SDL_GetTicks() - lastTick;
			lastTick = SDL_GetTicks();
			timer += delta;

			// Si está pensando y termina de pensar, pasa al estado de pedir la comida (reinicia el contador)
			if (state == THINKING && timer >= THINKINGTIME) {
			#ifdef _DEBUG
				cout << "I know what I want to eat" << endl;
			#endif
				state = EATING;	// TAKEMYORDER
				timer = 0;
			}
			// Si está comiendo y termina de comer, pasa al estado de caminar hacia la caja
			else if (state == EATING && timer >= EATINGTIME) {
				state = FINISH_EAT;
			#ifdef _DEBUG
				cout << "I'm done eating" << endl;
			#endif
			}
		}

		

	}

	// Función que asigna al plato pedido uno aleatorio de entre los
	// disponibles en el menú del día y cambia el estado a ORDERED
	void takeOrder() {
		int rndDish = rand() % availableDishes.size();
		orderedDish = (int)availableDishes[rndDish];

	#ifdef _DEBUG
		cout << "Order taken, I want " << orderedDish << endl;
	#endif
		state = ORDERED;

	}
	// Función que devuelve el plato que se ha pedido
	int getOrderedDish() { return orderedDish; }


	// Función que informa que ha sido servido y cambia el estado a EATING (reinicia el contador)
	void getServed() {
	#ifdef _DEBUG
		cout << "Thanks for the food" << endl;
	#endif
		state = EATING;
		timer = 0;
		lastTick = SDL_GetTicks();
	}


	void changeDish() {
		if (!dishChanged) {
			int lastDish = orderedDish;
			while (lastDish == orderedDish) {
				int rndDish = rand() % availableDishes.size();
				orderedDish = availableDishes[rndDish];
			}
		}
		else state = OUT;
	}

	void handleEvents() {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			if (state == TAKEMYORDER)
				takeOrder();
			else if (state == ORDERED)
				getServed();
		}
	}

};