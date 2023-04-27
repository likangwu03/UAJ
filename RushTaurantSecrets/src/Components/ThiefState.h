#pragma once
#include "../Structure/Component.h"
#include "../Utilities/SDLUtils.h"
#include "FreezerComp.h"
#include "../Structure/Scene.h"
#include "../Structure/GameManager.h"

class ThiefState : public Component {
public:
	enum States { 
		OBJECTIVE_SECRET, 
		OBJECTIVE_FREEZER, 
		SECRET, 
		FREEZER,
		DEAD, 
		ESCAPE 
	};

private:
	SDLUtils* sdl;
	States currentState;
	GameManager* gm;
	FreezerComp* freezer;
	float elapsedTime;
	float deadTime;
	SoundEffect* fridgeSound;
	SoundEffect* formulaSound;
	States randomObjective(bool canGetFreezer) {
		int max = canGetFreezer ? 2 : 1;
		return (States)sdl->rand().nextInt(0, max);
	}

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_STATE;

	ThiefState(GameObject* parent, bool canGetFreezer) :
		Component(parent, id), sdl(SDLUtils::instance()),
		gm(GameManager::get()), elapsedTime(0), deadTime(1 * 1000) ,
		fridgeSound(&sdlutils().soundEffects().at("OPEN_FRIDGE")),
		formulaSound(&sdlutils().soundEffects().at("REACH_FORMULA"))
	{
		formulaSound->setVolume(50);
		freezer = parent->getScene()->getGameObject(_ecs::hdr_FREEZER)->getComponent<FreezerComp>();
		currentState = randomObjective(canGetFreezer);
	}

	inline States getState() const {
		return currentState;
	}

	inline void setState(States state) {
		currentState = state;
	}

	inline void hasReachObjective() {
		currentState = (States)((int)currentState + 2);
	}

	virtual void update() {
		switch (currentState) {
		case ThiefState::SECRET:
			// se cambia al final en el que los ladrones han descubierto la fórmula secreta
			formulaSound->play();
			parent->setAlive(false);
			//gm->setGameOver(endingType::Robbed);
			break;

		case ThiefState::FREEZER:
			// se cambia al final en el que los ladrones han abierto el congelador
			freezer->isOpen();
			fridgeSound->play();
			if (gm->getHasKill()) {
			    parent->setAlive(false);	
				//gm->setGameOver(endingType::Caught);
			}
			else {
				currentState = ESCAPE;
			}			
			break;

		case DEAD:
			elapsedTime += deltaTime;
			if (elapsedTime > deadTime) {
				elapsedTime = 0;	// no haria falta

				gm->setHasKill(true);
				gm->killed();

				parent->setAlive(false);
			}
			break;
		}
	}
};