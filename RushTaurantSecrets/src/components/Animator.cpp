#include "Animator.h"

void Animator::addAnimation(Texture* t, int w, int h, int n)
{
	Anim a(t, w, h, n);
	animations.push_back(a);
}

void Animator::updateAnim()
{
	lastFrame = sdlutils().currRealTime();
	count++;

	if (sdlutils().currRealTime() - lastFrame > frameRate) {

		lastFrame = sdlutils().currRealTime();

		animations[currentAnim].sqrx = count * animations[currentAnim].width;
		count++;

		if (count * animations[currentAnim].sqrx > animations[currentAnim].maxFrames)
			count = 0;
	}
}
