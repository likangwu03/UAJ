#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"

using namespace std;
using Anim = std::pair<Texture*, int>;

class Animator : public Component
{
	Anim animation;

	int currentAnim;
	int count;
	float lastFrame;
	float frameRate;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_ANIMATOR;

	Animator(GameObject* parent, Texture* t, int endFrame) : Component(parent, id){
		animation = { t, endFrame };
		//fila de la animacion
		currentAnim = 0;
		count = 0;
		lastFrame = sdlutils().currRealTime();
		frameRate = 100;
		/*
		sqr.x = 0;
		sqr.y = 0;
		sqr.w = 16;
		sqr.h = 32;
		*/
	};
	Animator(GameObject* parent, Texture* t, int endFrame, int currAnim) : Component(parent, id) {
		animation = { t, endFrame };
		//fila de la animacion
		currentAnim = currAnim;
		count = 0;
		lastFrame = sdlutils().currRealTime();
		frameRate = 100;
		/*
		sqr.x = 0;
		sqr.y = 0;
		sqr.w = 16;
		sqr.h = 32;
		*/
	};
	~Animator() {};

	void updateAnim();
	void setCurrentAnim(int n, const int nframes);

	void update() {
		if (sdlutils().currRealTime() - lastFrame > frameRate) {
			lastFrame = sdlutils().currRealTime();
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
		animation.first->renderFrame(temp, count, currentAnim);
	};
};

