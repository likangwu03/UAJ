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
}

inline void ThiefTrigger::isInteractingWith() {
	// se indica al thievesManager con que jugador está interactuando el ladrón ahora mismo
	thievesManager->setThiefInteractWith(parent);
	// se muestran los controles de dicho ladrón
	showControl->setActive(true);
	// se le indica al ladrón que el jugador no puede matarle o hacerle escapar
	// hasta la siguiente vez
	playerHasPerformedAction = true;
}

void ThiefTrigger::hideButtons() {
	showControl->setActive(false);
}

bool ThiefTrigger::escape(bool keyPressed) {
	if (keyPressed) {
		thiefMovement->escape();
		escapeSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		escapeSound->play();
		hideButtons();
		interactWithNextThief();
		send(true);
		return true;
	}
	return false;
}

bool ThiefTrigger::die(bool keyPressed) {
	if (keyPressed) {
		thiefMovement->die();
		dieSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		dieSound->play();
		hideButtons();
		// si había overlap con más de un ladrón, se pasa a interactuar con el siguiente
		interactWithNextThief();
		send(false);
		return true;
	}
	return false;
}

void ThiefTrigger::interactWithNextThief() {
	vector<GameObject*> interactiveThieves = thievesManager->canInteractWith();
	// vector con los ladrones con los que puede interactuar
	if (!interactiveThieves.empty()) {
		// se coge el primero
		GameObject* thief = interactiveThieves.front();
		ThiefTrigger* thiefTrigger = thief->getComponent<ThiefTrigger>();
		// se indica que está interactuando con ese
		thiefTrigger->isInteractingWith();
	}
	else {
		thievesManager->setThiefInteractWith(nullptr);
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

		// se indica el ladrón con el que interactuar
		thievesManager->setThiefInteractWith(parent);
		showControl->setActive(true);
	}
}

void ThiefTrigger::onTriggerExit() {
	hideButtons();

	// si se ha dejado de hacer overlap con el ladrón que se estaba interactuando,
	// no se está interactuando con ninguno
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
	}
}

void ThiefTrigger::send(bool escape) {
	Message m(Message::msg_THIEF_INTERACT);
	m.thief_interact.escape = escape;
	thievesManager->send(parent, m);
}

void ThiefTrigger::escapeOrDie(bool escape) {
	if(escape) {
		thiefMovement->escape();
		escapeSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		escapeSound->play();
	} else {
		thiefMovement->die();
		dieSound->setVolume(GameManager::instance()->getSoundEffectsVolume());
		dieSound->play();
	}
	if(thievesManager->getThiefInteractWith() == parent) {
		hideButtons();
		interactWithNextThief();
	}
}