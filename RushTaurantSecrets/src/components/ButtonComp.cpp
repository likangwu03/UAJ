#include "ButtonComp.h"

#include "../sdlutils/InputHandler.h"

#include "../utils/checkML.h"

ButtonComp::ButtonComp(GameObject* parent, string hl, void(*callback)())  : Component(parent, id), 
	transform(parent->getComponent<Transform>()), highlighted(false)
{
	tf = parent->getComponent<Transform>();

	highlight = &sdlutils().images().at(hl);
	_callback = callback;
	dest.x = tf->getPos().getX();
	dest.y = tf->getPos().getY();
	dest.w = tf->getW();
	dest.h = tf->getH();

	ih().initialiseJoysticks();
	if (ih().joysticksInitialised())
		_joy = ih().getPlayerController(0);
}

void ButtonComp::handleEvents()
{
	int x, y; // corrdenadas del puntero del ratón
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 1, 1 };

	SDL_Rect dest = {transform->getPos().getX(), transform->getPos().getY(), transform->getW(), transform->getH()};

	if (SDL_HasIntersection(&mouseRect, &dest)) {
		highlighted = true;
		if (ih().getMouseButtonState(ih().LEFT)) {
			playSound();
			_callback();
		}
	}
	else if (ih().joysticksInitialised()) {
		highlighted = true;
		if (ih().getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
			ih().clean();
			ih().setControls(false);
			playSound();
			_callback();
		}
	}
	else {
		highlighted = false;
	}
}

bool ButtonComp::isHighlighted() {
	return highlighted;
}

void ButtonComp::render() {
	if (highlighted) {
		highlight->render(dest);
	}
}


void ButtonComp::playSound() {
	sdlutils().soundEffects().at("click_button").play();
}
