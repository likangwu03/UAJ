#include "UIAnimator.h"

#include "../utils/checkML.h"

void UIAnimator::init(Vector p) {
	if (pos.getX() == -1 && pos.getY() == -1) pos = plTf->getPos(); //si no le dan pos, se coge del transform
	else pos = p;
};

void UIAnimator::render() {
	SDL_Rect temp;

	if (plTf->isStatic()) {
		temp.x = pos.getX();
		temp.y = pos.getY();
	}

	else { //si no es est¨¢tico, seguir¨¢ siempre al transform
	temp.x = plTf->getPos().getX();
	temp.y = plTf->getPos().getY();
	}
	temp.w = width * sdlutils().getResizeFactor();
	temp.h = height * sdlutils().getResizeFactor();
	// indicas la columna y la fila del frame del spritesheet que quieres que se renderice
	texture->renderFrame(temp, currFrame, currentAnim, angle);
}

int UIAnimator::getFramesNumber() { return endFrame + 1; }

void UIAnimator::changeFrameRate(int newFrameRate) {
	frameRate = newFrameRate;
}