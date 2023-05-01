#include "ThiefTrigger.h"
#include "../Utilities/checkML.h"
#include "Transform.h"
#include "../Managers/ThievesManager.h"

ThiefTrigger::ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_), playerHasPerformedAction(false),
	escapeSound(&sdlutils().soundEffects().at("ESCAPE_THIEF")),
	dieSound(&sdlutils().soundEffects().at("KILL_THIEF")) {
	parentTransform = parent->getComponent<Transform>();
	thiefMovement = parent->getComponent<ThiefMovement>();
	thiefState = parent->getComponent<ThiefState>();
	showControl = new ShowControlAuto(parent, {
		{ControlsType::key_E,ControlsType::play_Cross,ControlsType::xbox_A, Vector(KILL_X_OFFSET, KILL_Y_OFFSET),WIDTH,HEIGHT},
		{ControlsType::key_Q,ControlsType::play_Circle, ControlsType::xbox_B,Vector(RUN_X_OFFSET,RUN_Y_OFFSET),WIDTH,HEIGHT}
		}, parentTransform);
	runTexture = &((sdlutils()).images().at("RUN_ICON"));
	killTexture = &((sdlutils()).images().at("KILL_ICON"));
	thievesManager = ThievesManager::get();

	//controles encima
	//showControl = new ShowControlAuto(parent, { {ControlsType::key_E,ControlsType::play_Cross,ControlsType::xbox_A, Vector(0,-16),32,32}, 
	//	{ControlsType::key_Q,ControlsType::play_Circle, ControlsType::xbox_B,Vector(40,-16),32,32} }, parent->getComponent<Transform>());
}

inline void ThiefTrigger::isInteractingWith() {
	// se indica al thievesManager con que jugador est� interactuando el ladr�n ahora mismo
	thievesManager->setThiefInteractWith(parent);
	// se muestran los controles de dicho ladr�n
	showControl->setActive(true);
	// se le indica al ladr�n que el jugador no puede matarle o hacerle escapar
	// hasta la siguiente vez
	playerHasPerformedAction = true;
}

void ThiefTrigger::hideButtons() {
	showControl->setActive(false);
}

bool ThiefTrigger::escape(bool keyPressed) {
	if (keyPressed) {
		thiefMovement->escape();
		escapeSound->play();
		hideButtons();
		interactWithNextThief();
		return true;
	}
	return false;
}

bool ThiefTrigger::die(bool keyPressed) {
	if (keyPressed) {
		thiefMovement->die();
		dieSound->play();
		hideButtons();
		// si hab�a overlap con m�s de un ladr�n, se pasa a interactuar con el siguiente
		interactWithNextThief();
		return true;
	}
	return false;
}

void ThiefTrigger::interactWithNextThief() {
	// vector con los ladrones con los que puede interactuar
	if (!thievesManager->canInteractWith().empty()) {
		// se coge el primero
		GameObject* thief = thievesManager->canInteractWith().front();
		ThiefTrigger* thiefTrigger = thief->getComponent<ThiefTrigger>();
		// se indica que est� interactuando con ese
		thiefTrigger->isInteractingWith();
	}
}

void ThiefTrigger::isOverlapping() {
	if (thievesManager->getThiefInteractWith() == parent && !playerHasPerformedAction) {
		if (ih->joysticksInitialised()) {
			// si no ha escapado, se comprueba si se le ha matado
			if (!escape(ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B))) {
				die(ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A));
			}
		}
		else {
			if (!escape(ih->isKeyDown(SDLK_q))) {
				die(ih->isKeyDown(SDLK_e));
			}
		}
	}
	else {
		playerHasPerformedAction = false;
	}
}

void ThiefTrigger::onTriggerEnter() {
	if ((thiefState->getState() == ThiefState::OBJECTIVE_SECRET ||
		thiefState->getState() == ThiefState::OBJECTIVE_FREEZER) &&
		thievesManager->getThiefInteractWith() == nullptr) {

		// se indica el ladr�n con el que interactuar
		thievesManager->setThiefInteractWith(parent);
		showControl->setActive(true);
	}
}

void ThiefTrigger::onTriggerExit() {
	hideButtons();

	// si se ha dejado de hacer overlap con el ladr�n que se estaba interactuando,
	// no se est� interactuando con ninguno
	if (thievesManager->getThiefInteractWith() == parent) {
		thievesManager->setThiefInteractWith(nullptr);
	}
}

void ThiefTrigger::render() {
	if (showControl->isActive()) {
		SDL_Rect dest;
		dest.x = parentTransform->getPos().getX() + (RUN_X_OFFSET - 15);
		dest.y = parentTransform->getPos().getY() + (RUN_Y_OFFSET * -3);
		dest.w = WIDTH;
		dest.h = HEIGHT;
		runTexture->render(dest);

		dest.x = parentTransform->getPos().getX() + KILL_X_OFFSET - 15;
		killTexture->render(dest);

		//dest.x = parentTransform->getPos().getX() + (X_OFFSET * 1.3);
		//dest.y = parentTransform->getPos().getY() + RUN_Y_OFFSET - 15;
		//dest.w = WIDTH;
		//dest.h = HEIGHT;
		//runTexture->render(dest);

		//dest.y = parentTransform->getPos().getY() + KILL_Y_OFFSET - 15;
		//killTexture->render(dest);
	}
}

