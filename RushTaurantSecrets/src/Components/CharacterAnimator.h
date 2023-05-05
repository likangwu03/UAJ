#pragma once
#include "Animator.h"
using namespace std;

/*pos sigue la del transform, pero se puede definir independientemente w y h*/
class CharacterAnimator :public Animator {
protected:
	GOOrientation parentOrientation;
	GOOrientation currOrientation;
	movementState parentMov;
	movementState currMov;
	bool hasOrientation;

	void init();

public:

	constexpr static _ecs::_cmp_id id = _ecs::cmp_CHARACANIM;

	CharacterAnimator(GameObject* parent, Texture* t, AnimParams aP) :
		Animator(parent, t, aP, id), hasOrientation(true) {
		init();
	}

	CharacterAnimator(GameObject* parent, string s, AnimParams aP) :
		Animator(parent, s, aP, id), hasOrientation(true) {
		init();
	}

	virtual void update();
};