#include "Animator.h"

Animator::Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim = 0, int frRate) : Component(parent, id), sdl(SDLUtils::instance()) {
	texture = t;
	able = true;
	setCurrentAnim(iniFrame, endFrame, currAnim);
	lastTic = sdlutils().currRealTime();
	frameRate = 100;
	parentOrientation = parent->getOrientation();
	currOrientation = parent->getOrientation();
	plTf = parent->getComponent<Transform>();
	plMov = parent->getComponent<PlayerMovementController>();
};

Animator::Animator(GameObject* parent, string s, int iniFrame, int endFrame, int currAnim = 0, int frRate) : Component(parent, id), sdl(SDLUtils::instance()) {
	texture = &((*sdl).images().at(s));
	//fila de la animacion
	setCurrentAnim(iniFrame, endFrame, currAnim);
	lastTic = sdlutils().currRealTime();
	frameRate = frRate;
};
/*mover al siguiente frame*/
void Animator::updateAnim() {
	++currFrame;

	if (currFrame >= endFrame)
		currFrame = initFrame;
}
/*cambiar de frame*/
void Animator::setCurrentAnim(int iniFram, int endFram, int currAnim)
{
	currentAnim = currAnim;
	endFrame = endFram;
	initFrame = iniFram;
	currFrame = iniFram;
}
/*cambiar de textura dada la textura*/
void Animator::setTexture(Texture* t, int iniFrame, int endFrame, int currAnim = 0, int frRate) {
	texture = t;
	setCurrentAnim(iniFrame, endFrame, currAnim);
}
/*cambiar de textura dado el nombre de textura*/
void Animator::setTexture(string s, int iniFrame, int endFrame, int currAnim = 0, int frRate) {
	texture = &((*sdl).images().at(s));
	setCurrentAnim(iniFrame, endFrame, currAnim);
}
void Animator::setAble(bool b) {
	able = b;
}
void Animator::update() {
	if (able) {
		if (plMov != nullptr) {
			if (!plMov->isMoving()) currentAnim = 1;
			else currentAnim = 2;
		}
		parentOrientation = parent->getOrientation();
		if (currOrientation != parentOrientation) {
			currOrientation = parentOrientation;
			if (currOrientation == east) {
				setCurrentAnim(0, 6, currentAnim);
			}
			else if (parent->getOrientation() == north) {
				setCurrentAnim(6, 12, currentAnim);
			}
			else if (parent->getOrientation() == west) {
				setCurrentAnim(12, 18, currentAnim);
			}
			else if (parent->getOrientation() == south) {
				setCurrentAnim(18, 24, currentAnim);
			}
		}
		if (sdlutils().currRealTime() - lastTic > frameRate) {
			lastTic = sdlutils().currRealTime();
			updateAnim();
		}
	}
}
void Animator::render()
{
	if (able) {
		SDL_Rect temp;
		temp.x = plTf->getPos().getX();
		temp.y = plTf->getPos().getY();
		temp.w = 48;
		temp.h = 96;
		// indicas la columna y la fila del frame del spritesheet que quieres que se renderice
		texture->renderFrame(temp, currFrame, currentAnim);
	}
};
