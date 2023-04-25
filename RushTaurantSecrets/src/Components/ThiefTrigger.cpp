#include "ThiefTrigger.h"
#include "../Utilities/checkML.h"
#include "Transform.h"

ThiefTrigger::ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
	TriggerComp(parent, pos_, width_, height_),
	escapeSound(&sdlutils().soundEffects().at("ESCAPE_THIEF")),
	dieSound(&sdlutils().soundEffects().at("KILL_THIEF"))
{
	parentTransform = parent->getComponent<Transform>();
	thiefMovement = parent->getComponent<ThiefMovement>();
	thiefState = parent->getComponent<ThiefState>();
	showControl = new ShowControlAuto(parent, { {ControlsType::key_E,ControlsType::play_Cross,ControlsType::xbox_A, Vector(X_OFFSET, KILL_Y_OFFSET),WIDTH,HEIGHT}, 
		{ControlsType::key_Q,ControlsType::play_Circle, ControlsType::xbox_B,Vector(X_OFFSET,RUN_Y_OFFSET),WIDTH,HEIGHT} }, parentTransform);
	runTexture = &((sdlutils()).images().at("RUN_ICON"));
	killTexture = &((sdlutils()).images().at("KILL_ICON"));

	//controles encima
	//showControl = new ShowControlAuto(parent, { {ControlsType::key_E,ControlsType::play_Cross,ControlsType::xbox_A, Vector(0,-16),32,32}, 
	//	{ControlsType::key_Q,ControlsType::play_Circle, ControlsType::xbox_B,Vector(40,-16),32,32} }, parent->getComponent<Transform>());
}

void ThiefTrigger::hideButtons()
{
	showControl->setActive(false);
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
		showControl->setActive(true);
	}
}

void ThiefTrigger::onTriggerExit()
{
	hideButtons();
}

void ThiefTrigger::render()
{
	if (showControl->isActive())
	{
		SDL_Rect dest;
		dest.x = parentTransform->getPos().getX() + (X_OFFSET * 1.3);
		dest.y = parentTransform->getPos().getY() + RUN_Y_OFFSET - 15;
		dest.w = WIDTH;
		dest.h = HEIGHT;
		runTexture->render(dest);

		dest.y = parentTransform->getPos().getY() + KILL_Y_OFFSET - 15;
		killTexture->render(dest);
	}
}

