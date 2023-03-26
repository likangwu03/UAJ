#include "ThiefTrigger.h"
#include "../Utilities/checkML.h"

ThiefTrigger::ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_) {
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
				hideButtons();
			}
			else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
				thiefMovement->die();
				hideButtons();
			}
		}
		else {
			if (ih->isKeyDown(SDLK_q)) {
				thiefMovement->escape();
				hideButtons();
			}
			else if (ih->isKeyDown(SDLK_e)) {
				thiefMovement->die();
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

