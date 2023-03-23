#include "ThiefTrigger.h"
#include "../Utilities/checkML.h"

ThiefTrigger::ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_)
{
	tMovement = parent->getComponent<ThiefMovement>();
	mRender = parent->getComponent<MurderRender>();
	sRender = parent->getComponent<ShooRender>();
}

void ThiefTrigger::killPressed()
{
	tMovement->die();
	mRender->setActive(false);
	sRender->setActive(false);
}

void ThiefTrigger::isOverlapping()
{
	if (ih->joysticksInitialised()) {
		if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B)) {
			tMovement->escape();
		}
		else if (ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
			killPressed();
		}
	}
	else {
		if (ih->isKeyDown(SDLK_q)) {
			tMovement->escape();
		}
		else if (ih->isKeyDown(SDLK_e)) {
			killPressed();
		}
	}

}

void ThiefTrigger::onTriggerEnter()
{
	if (tMovement->getState() != ThiefMovement::DEAD) {
		mRender->setActive(true);
		sRender->setActive(true);
	}
}

void ThiefTrigger::onTriggerExit()
{
	mRender->setActive(false);
	sRender->setActive(false);
}

