#include "Animator.h"

void Animator::addAnimation(Texture* t, int n)
{
	Anim a{t, n};
	animations.push_back(a);
}

void Animator::updateAnim()
{
	lastFrame = sdlutils().currRealTime();

	sqr.x = count * sqr.w;

	count++;

	if (count >= animations[currentAnim].second)
		count = 0;
}