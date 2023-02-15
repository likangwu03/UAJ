#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"

using namespace std;
class Animator : public Component
{
	Texture* texture;
	int currentAnim;
	int initFrame;
	int endFrame;
	int currFrame;
	float lastTic;
	float frameRate;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_ANIMATOR;

	Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim = 0) : Component(parent, id) {
		texture = t;
		//fila de la animacion
		setCurrentAnim(iniFrame, endFrame, currAnim);
		lastTic = sdlutils().currRealTime();
		frameRate = 100;
		/*
		sqr.x = 0;
		sqr.y = 0;
		sqr.w = 16;
		sqr.h = 32;
		*/
	};
	virtual ~Animator() {};

	void updateAnim() {
		++currFrame;

		if (currFrame >= endFrame)
			currFrame = initFrame;
	}
	void setCurrentAnim(int iniFram, int endFram, int currAnim = 0)
	{
		currentAnim = currAnim;
		endFrame = endFram;
		initFrame = iniFram;
		currFrame = iniFram;
	}

	void update() {
		if (sdlutils().currRealTime() - lastTic > frameRate) {
			lastTic = sdlutils().currRealTime();
			updateAnim();
		}
	}
	virtual void render()
	{
		SDL_Rect temp;
		temp.x = parent->getComponent<Transform>()->getPos().getX();
		temp.y = parent->getComponent<Transform>()->getPos().getY();
		temp.w = 48;
		temp.h = 96;

		// indicas la columna y la fila del frame del spritesheet que quieres que se renderice
		texture->renderFrame(temp, currFrame, currentAnim);
	};
};