#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/StraightMovement.h"
#include "../Components/CharacterAnimator.h"
#include "../Structure/Scene.h"

class DancingClient : public GameObject {
private:
	int width;
	int height;

public:
	DancingClient(Scene* scene) : GameObject(scene), width(48), height(96) {
		new Transform(this, Vector(0, 0), Vector(0, 0), width, height);
		StraightMovement* s = new StraightMovement(this, 5);
		s->setWalkingState(pushing);
		int aux = SDLUtils::instance()->rand().nextInt(1, 15);
		Animator::AnimParams aP;
		aP.initFrame = 18;
		aP.endFrame = 24;
		aP.initFrame = 1;
		new CharacterAnimator(this, "Client_" + to_string(aux), aP);

		scene->pushRenderList(Down, this);
	}
};