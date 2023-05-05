#pragma once
#include "../Structure/Component.h"
#include "../Definitions/Food_def.h"
#include "ClientStateRender.h"
#include <SDL.h>

using namespace std;
using namespace _ecs;

class ClientState : public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STATE;
	ClientState(GameObject* parent, vector<_ecs::DishInfo>* menu);

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

	void unhappy() {
		happiness = 0;
	}

private:
	States state;

	const int THINKINGTIME = 5000, EATINGTIME = 5000, DECREASEHAPPINESS = 10;
	float decreaseFreq, reputationDecrease;
	float happiness, timer;

	vector<_ecs::DishInfo>* availableDishes;
	ClientStateRender* render;
	_ecs::_dish_id orderedDish;
	bool dishChanged;
	SoundEffect* takeNote;
public:

	void update();
	void takeOrder();
	void takeOrder(int dish);
	_ecs::_dish_id getOrderedDish();
	void getServed(bool send=true);
	void changeDish(bool send=true);
	float getHappiness();


	void receive(const Message& message) override;
};