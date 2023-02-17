#include "Animator.h"

Animator::Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim = 0, int frRate = FRAMERATE) : Component(parent, id), sdl(SDLUtils::instance()) {
	texture = t;
	setCurrentAnim(iniFrame, endFrame, currAnim);
	lastTic = sdlutils().currRealTime();
	frameRate = 100;
	parentOrientation = parent->getOrientation();
	currOrientation = parent->getOrientation();
};

Animator::Animator(GameObject* parent, string s, int iniFrame, int endFrame, int currAnim = 0, int frRate = FRAMERATE) : Component(parent, id), sdl(SDLUtils::instance()) {
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
void Animator::setCurrentAnim(int iniFram, int endFram, int currAnim = 0)
{
	currentAnim = currAnim;
	endFrame = endFram;
	initFrame = iniFram;
	currFrame = iniFram;
}
/*cambiar de textura dada la textura*/
void Animator::setTexture(Texture* t, int iniFrame, int endFrame, int currAnim = 0, int frRate = FRAMERATE) {
	texture = t;
	setCurrentAnim(iniFrame, endFrame, currAnim);
}
/*cambiar de textura dado el nombre de textura*/
void Animator::setTexture(string s, int iniFrame, int endFrame, int currAnim = 0, int frRate = FRAMERATE) {
	texture = &((*sdl).images().at(s));
	setCurrentAnim(iniFrame, endFrame, currAnim);
}
void Animator::update() {
	if (parent->getComponent<PlayerMovementController>() != nullptr) {
		if (!parent->getComponent<PlayerMovementController>()->isMoving()) currentAnim = 1;
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
void Animator::render()
{
	SDL_Rect temp;
	temp.x = parent->getComponent<Transform>()->getPos().getX();
	temp.y = parent->getComponent<Transform>()->getPos().getY();
	temp.w = 48;
	temp.h = 96;
	// indicas la columna y la fila del frame del spritesheet que quieres que se renderice
	texture->renderFrame(temp, currFrame, currentAnim);
};
