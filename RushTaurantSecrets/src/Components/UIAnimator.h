#pragma once
#include "Animator.h"
using namespace std;

class UIAnimator :public Animator {
protected:
	Vector pos;
	void init(Vector p); //no hereda del padre

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_UIANIM;

	UIAnimator(GameObject* parent, Texture* t, AnimParams aP, Vector pos = (-1, -1)) :
		Animator(parent, t, aP, id) { init(pos); }

	UIAnimator(GameObject* parent, string s, AnimParams aP, Vector pos = (-1, -1)) :
		Animator(parent, s, aP, id ) { init(pos); }
	
	/*cambiar de pos*/
	void setPos(Vector pos) { this->pos = pos; }
	/*si es estetico, usara siempre pos, si no, la del transform*/
	virtual void render();

	void changeFrameRate( int newFrameRate);
	int getFramesNumber();

};



