#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/StraightMovement.h"
#include "../Components/CharacterAnimator.h"
#include "../Structure/Scene.h"

class ClientMarket : public GameObject {
private:
	int width;
	int height;
	Animator::AnimParams aP;

public:
	ClientMarket(Scene* scene, string sprite, _ecs::RenderPos renderPos, float speed = 0, Vector initPos = Vector(0, 0)) :
		GameObject(scene), width(48), height(96), aP() {
		new Transform(this, RelativeToGlobal::pointRestaurant(initPos), Vector(0, 0), width, height);
		StraightMovement* s = new StraightMovement(this, speed);
		aP.initFrame = 18;
		aP.endFrame = 24;
		aP.currAnim = 1;
		new CharacterAnimator(this, sprite, aP);

		scene->pushRenderList(renderPos, this);
	}
};