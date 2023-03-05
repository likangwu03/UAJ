#include "Animator.h"

#include "../utils/checkML.h"

Animator::Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim, int frRate, float w, float h, _ecs::_cmp_id id) : Component(parent, id), sdl(SDLUtils::instance()) {
	texture = t;
	init(iniFrame, endFrame, currAnim, frRate, w, h);
};

Animator::Animator(GameObject* parent, string s, int iniFrame, int endFrame, int currAnim, int frRate, float w, float h, _ecs::_cmp_id id) : Component(parent, id), sdl(SDLUtils::instance()) {
	texture = &((*sdl).images().at(s));
	init(iniFrame, endFrame, currAnim, frRate, w, h);
};

void Animator::init(int iniFrame, int endFrame, int currAnim, int frRate, float w, float h) {
	setCurrentAnim(iniFrame, endFrame, currAnim);
	lastTic = sdlutils().currRealTime();
	frameRate = frRate;
	angle = 0;
	plTf = parent->getComponent<Transform>();

	if (w == 0 && h == 0) { //si no se define w y h, se coge del transform
		width = plTf->getW();
		height = plTf->getH();
	}
	else { //si se define w y h
		width = w;
		height = h;
	}
};

/*mover al siguiente frame*/
void Animator::updateAnim() {
	++currFrame;

	if (currFrame >= endFrame)
		currFrame = initFrame;
}
/*cambiar de frame*/
void Animator::setCurrentAnim(int iniFram, int endFram, int currAnim) {
	currentAnim = currAnim;
	endFrame = endFram;
	initFrame = iniFram;
	currFrame = iniFram;
}
/*cambiar de textura dada la textura*/
void Animator::setTexture(Texture* t, int iniFrame, int endFrame, int currAnim, int frRate) {
	texture = t;
	frameRate = frRate;
	setCurrentAnim(iniFrame, endFrame, currAnim);
}
/*cambiar de textura dado el nombre de textura*/
void Animator::setTexture(string s, int iniFrame, int endFrame, int currAnim, int frRate) {
	texture = &((*sdl).images().at(s));
	frameRate = frRate;

	setCurrentAnim(iniFrame, endFrame, currAnim);
}


void Animator::update() {

	if (sdlutils().currRealTime() - lastTic > frameRate) {
		lastTic = sdlutils().currRealTime();
		updateAnim();
	}
}

void Animator::render() {
	SDL_Rect temp;
	temp.x = plTf->getPos().getX();
	temp.y = plTf->getPos().getY();
	temp.w = width * sdlutils().getResizeFactor();
	temp.h = height * sdlutils().getResizeFactor();
	// indicas la columna y la fila del frame del spritesheet que quieres que se renderice
	texture->renderFrame(temp, currFrame, currentAnim, angle);
};