#pragma once
#include "../structure/Component.h"
#include "ClientState.h"
#include <SDL.h>

#include "../sdlutils/InputHandler.h"
using namespace std;

class ClientInTableState : public Component {
private:
	const int THINKINGTIME = 5000, EATINGTIME = 5000, LIMITIME = 10000;
	int limitTime, timer, lastTick;
	ClientState* clState;


public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CLIENTINTABLE;
	
	ClientInTableState(GameObject* parent, ClientState* cs) : Component(parent, id) {
		clState = cs;
		timer = 0; lastTick = 0;
	}

	void update() {
		if ( (clState->getState() == clState->THINKING || clState->getState() == clState->TAKEMYORDER || clState->getState() == clState->ORDERED) && timer >= LIMITIME) {
			clState->setState(clState->OUT);
#ifdef _DEBUG
			cout << "Leaving cus' I'm mad :(" << endl;
#endif
		}
		else if (clState->getState() == clState->THINKING) {
			if (timer >= THINKINGTIME){
#ifdef _DEBUG
				cout << "Pls take my order istg" << endl;
#endif
				clState->setState(clState->TAKEMYORDER);
			}
		}
		else if (clState->getState() == clState->EATING) {
			if (timer >= EATINGTIME) {
#ifdef _DEBUG
				cout << "Gotta pay" << endl;
#endif
				clState->setState(clState->REGISTER);

				this->alive = false;
			}
		}

		int delta = SDL_GetTicks() - lastTick;
		lastTick = SDL_GetTicks();
		timer += delta;
	}


	void takeOrder() {
		timer = 0;
#ifdef _DEBUG
		cout << "I want your entire stock" << endl;
#endif
		clState->setState(clState->ORDERED);
	}

	void getServed() { 
		timer = 0;
#ifdef _DEBUG
		cout << "Mmmmm so good and tasty" << endl;
#endif
		clState->setState(clState->EATING);
	}

	void handleEvents() {
		if (InputHandler::instance()->isKeyDown(SDLK_SPACE)) {
			if (clState->getState() == clState->TAKEMYORDER)
				takeOrder();
			else if (clState->getState() == clState->ORDERED)
				getServed();
		}
	}

};