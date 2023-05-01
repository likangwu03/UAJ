#include "ThiefState.h"

ThiefState::ThiefState(GameObject* parent, bool canGetFreezer) :
	Component(parent, id), sdl(SDLUtils::instance()),
	gm(GameManager::get()), elapsedTime(0), deadTime(1 * 1000),
	fridgeSound(&sdlutils().soundEffects().at("OPEN_FRIDGE")),
	formulaSound(&sdlutils().soundEffects().at("REACH_FORMULA")) {
	formulaSound->setVolume(50);
	freezer = parent->getScene()->getGameObject(_ecs::hdr_FREEZER)->getComponent<FreezerComp>();
	currentState = randomObjective(canGetFreezer);
}

void ThiefState::update() {
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