#include "ThiefTrigger.h"
#include "../Utilities/checkML.h"

ThiefTrigger::ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	escapeSound(&sdlutils().soundEffects().at("ESCAPE_THIEF")),
	dieSound(&sdlutils().soundEffects().at("KILL_THIEF"))
{
	thiefMovement = parent->getComponent<ThiefMovement>();
	thiefState = parent->getComponent<ThiefState>();
	mRender = parent->getComponent<MurderRender>();
	sRender = parent->getComponent<ShooRender>();
}

void ThiefTrigger::hideButtons()
{
	mRender->setActive(false);
	sRender->setActive(false);
}

void ThiefTrigger::isOverlapping() {
	if (thiefState->getState() == ThiefState::OBJECTIVE_SECRET && ThiefState::OBJECTIVE_FREEZER) {
		if (ih->joysticksInitialised()) {
			if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) {
				thiefMovement->escape();
				escapeSound->play();
				hideButtons();
			}
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
				thiefMovement->die();
				dieSound->play();
				hideButtons();
			}
		}
		else {
			if (ih->isKeyDown(SDLK_q)) {
				thiefMovement->escape();
				escapeSound->play();
				hideButtons();
			}
			else if (ih->isKeyDown(SDLK_e)) {
				thiefMovement->die();
				dieSound->play();
				hideButtons();
			}
		}
	}
}

void ThiefTrigger::onTriggerEnter()
{
	if (thiefState->getState() == ThiefState::OBJECTIVE_SECRET && ThiefState::OBJECTIVE_FREEZER) {
		mRender->setActive(true);
		sRender->setActive(true);
	}
}

void ThiefTrigger::onTriggerExit()
{
	hideButtons();
}

