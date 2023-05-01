#include "Animator.h"

#include "../Utilities/checkML.h"

void Animator::init(AnimParams aP)
{
	setCurrentAnim(aP.initFrame, aP.endFrame, aP.currAnim);
	lastTic = sdlutils().currRealTime();
	animationParameters.frameRate = aP.frameRate;
	angle = 0;
	plTf = parent->getComponent<Transform>();

	if (aP.width == 0 && aP.height == 0) { //si no se define w y h, se coge del transform
		animationParameters.width = plTf->getW();
		animationParameters.height = plTf->getH();
	}
	else { //si se define w y h
		animationParameters.width = aP.width;
		animationParameters.height = aP.height;
	}
}

Animator::Animator(GameObject* parent, Texture* t, AnimParams aP, _ecs::_cmp_id id) : Component(parent, id), sdl(SDLUtils::instance())
{
	texture = t;
	init(aP);
}
Animator::Animator(GameObject* parent, string s, AnimParams aP, _ecs::_cmp_id id) : Component(parent, id), sdl(SDLUtils::instance())
{
	texture = &((*sdl).images().at(s));
	init(aP);
}

/*mover al siguiente frame*/
void Animator::updateAnim() {
	++currFrame;

	if (currFrame >= animationParameters.endFrame)
		currFrame = animationParameters.initFrame;
}
/*cambiar de frame*/
void Animator::setCurrentAnim(int iniFram, int endFram, int currAnim) {
	animationParameters.currAnim = currAnim;
	animationParameters.endFrame = endFram;
	animationParameters.initFrame = iniFram;
	currFrame = iniFram;
}
/*cambiar de textura dada la textura*/
void Animator::setTexture(Texture* t, int iniFrame, int endFrame, int currAnim, int frRate) {
	texture = t;
	animationParameters.frameRate = frRate;
	setCurrentAnim(iniFrame, endFrame, currAnim);
}
/*cambiar de textura dado el nombre de textura*/
void Animator::setTexture(string s, int iniFrame, int endFrame, int currAnim, int frRate) {
	texture = &((*sdl).images().at(s));
	animationParameters.frameRate = frRate;

	setCurrentAnim(iniFrame, endFrame, currAnim);
}


void Animator::update() {
	lastTic += deltaTime / 10;
	if (lastTic > animationParameters.frameRate ) {
		lastTic = 0;
		updateAnim();
	}
}

void Animator::render() {
	SDL_Rect temp;
 	temp.x = plTf->getPos().getX();
	temp.y = plTf->getPos().getY();
	temp.w = animationParameters.width * sdlutils().getResizeFactor();
	temp.h = animationParameters.height * sdlutils().getResizeFactor();
	// indicas la columna y la fila del frame del spritesheet que quieres que se renderice
	texture->renderFrame(temp, currFrame, animationParameters.currAnim, angle);
};