#include "Animator.h"

void Animator::addAnimation(Texture* t, int endFrame)
{
	Anim a{t, endFrame};
	animations.push_back(a);
}

void Animator::updateAnim()
{
	++count;

	if (count >= animations[currentAnim].second)
		count = 0;
}

void Animator::setCurrentAnim(const int n)
{
	currentAnim = n;
}
