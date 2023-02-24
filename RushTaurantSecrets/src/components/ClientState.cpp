#include "ClientState.h"

#include "../objects/Reputation.h"

#include "../utils/checkML.h"

ClientState::ClientState(GameObject* parent, const vector<_ecs::_dish_id> menu) : Component(parent, id),
	state(START), happiness(80), timer(0), lastTick(sdlutils().currRealTime()), 
	availableDishes(menu), orderedDish(NONE_DISH), dishChanged(false), render(parent->getComponent<ClientStateRender>()) {
	render->clientStateIsReady(); //decirle que ya est¨¢ creado
}


ClientState::States ClientState::getState() const { return state; }

void ClientState::setState(States state) { 
	lastTick = sdlutils().currRealTime();
	timer = 0;
	this->state = state;
}


void ClientState::update() {
	int delta = sdlutils().currRealTime() - lastTick;
	lastTick = sdlutils().currRealTime();
	

	// Si est?en estados en los que el jugador tenga que interactuar con él, va bajando la felicidad poco a poco
	if (state == ENTRANCE || state == TAKEMYORDER || state == ORDERED || state == PAYING) {
		if (delta < 100)
			happiness -= DECREASE;

		// Si la felicidad llega a 0, se pone el estado a OUT
		// (DE MOMENTO TARDA COMO 1 MINUTO)
		if (happiness <= 0) {
			setState(OUT);
			Reputation::instance()->reduceReputation(5);
			render->renderEatingState();
#ifdef _DEBUG
			cout << "Happiness reached 0, leaving restaurant" << endl;
#endif
		}
	}
	// Si no, si est?pensando o comiendo, se actualiza el temporizador de lo que tarda en realizar la acción
	else if (state == THINKING || state == EATING) {
		if (delta < 100)
			timer += delta;

		// Si est?pensando y termina de pensar, pasa al estado de pedir la comida (reinicia el contador)
		if (state == THINKING && timer >= THINKINGTIME) {
#ifdef _DEBUG
			cout << "I know what I want to eat" << endl;
#endif
			setState(TAKEMYORDER);
			render->renderTakingNoteState();
		}
		// Si est?comiendo y termina de comer, pasa al estado de caminar hacia la caja
		else if (state == EATING && timer >= EATINGTIME) {
			setState(FINISH_EAT);
#ifdef _DEBUG
			cout << "I'm done eating" << endl;
#endif
		}
	}


}


// Función que asigna al plato pedido uno aleatorio de entre los
// disponibles en el men?del día y cambia el estado a ORDERED
void ClientState::takeOrder() {
	int rndDish;
	// Si no se ha cambiado el plato, escoge uno aleatorio
	if (!dishChanged) {
		rndDish = rand() % availableDishes.size();
		orderedDish = availableDishes[rndDish];
	}
	// Si se ha cambiado el plato, escoge uno 
	// aleatorio hasta que sea diferente del anterior
	else {
		_ecs::_dish_id lastDish = orderedDish;
		while (lastDish == orderedDish) {
			 rndDish = rand() % availableDishes.size();
			orderedDish = availableDishes[rndDish];
		}
	}

#ifdef _DEBUG
	cout << "Order taken, I want " << rndDish << endl;
#endif
	setState(ORDERED);
	render->renderOrderingState();
}


// Función que devuelve el plato que se ha pedido
_ecs::_dish_id ClientState::getOrderedDish() { return orderedDish; }


// Función que informa que ha sido servido y cambia el estado a EATING
void ClientState::getServed() {
#ifdef _DEBUG
	cout << "Thanks for the food" << endl;
#endif
	setState(EATING);
	render->renderEatingState();
}


// Función que hace que el cliente vuelva al estado de pensar si no se le ha 
// cambiado y le baja la felicidad o hace que se vaya si se le ha cambiado antes 
void ClientState::changeDish() {
	if (!dishChanged) {
		dishChanged = true;
		happiness -= 20;
		setState(THINKING);
		render->renderThinkingState();
	}
	else setState(OUT);
}


// Función que devuelve la felicidad del cliente
float ClientState::getHappiness() {
	return happiness;
}