#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/PlayerMovementController.h"

using namespace std;
class Animator : public Component
{
	Texture* texture;
	//fila de la anim
	int currentAnim;
	int initFrame;
	int endFrame;
	//columna de la anim
	int currFrame;
	float lastTic;
	float frameRate;
	GOOrientation parentOrientation;
	GOOrientation currOrientation;

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_ANIMATOR;

	Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim = 0) : Component(parent, id) {
		texture = t;
		setCurrentAnim(iniFrame, endFrame, currAnim);
		lastTic = sdlutils().currRealTime();
		frameRate = 100;
		parentOrientation = parent->getOrientation();
		currOrientation = parent->getOrientation();
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
		if (parent->getComponent<PlayerMovementController>() != nullptr) {
			if (!parent->getComponent<PlayerMovementController>()->isMoving()) {
				currentAnim = 1;
			}
			else
				currentAnim = 2;
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