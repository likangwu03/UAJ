#pragma once
#include "Animator.h"
using namespace std;

/*pos seguir¨¢ la del transform, pero se puede definir independientemente w y h*/
class CharacterAnimator :public Animator
{
protected:
	GOOrientation parentOrientation;
	GOOrientation currOrientation;
	movementState parentMov;
	movementState currMov;

	void init();
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_CHARACANIM;

	CharacterAnimator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim = 0, int frRate = FRAMERATE, float w = 0, float h = 0) :
		Animator(parent, t, iniFrame, endFrame, currAnim, frRate, w, h,id) {init();}

	CharacterAnimator(GameObject* parent, string s, int iniFrame, int endFrame, int currAnim = 0, int frRate = FRAMERATE, float w = 0, float h = 0) :
		Animator(parent, s, iniFrame, endFrame, currAnim, frRate, w, h,id) {init();}
	
	virtual void update();
};

