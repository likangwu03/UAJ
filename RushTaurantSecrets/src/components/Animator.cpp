#include "Animator.h"

void Animator::updateAnim()
{
	++count;

	if (count >= animation.second)
		count = 0;
}

void Animator::setCurrentAnim(const int n, const int nframes)
{
	currentAnim = n;
	animation.second = nframes;
	count = 0;
}
