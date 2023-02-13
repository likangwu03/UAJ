#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;

struct Anim {
	Texture* animSS;
	int sqrx, sqry, width, height, maxFrames;

	//n es el numero de frames que tiene la animacion
	Anim(Texture* t, int w, int h, int n) {
		animSS = t;
		sqrx = 0;
		sqry = 0;
		width = w;
		height = h;
		maxFrames = n;
	}
};

class Animator : public Component
{
	vector<Anim> animations;

	int currentAnim;
	int count;
	float lastFrame;
	float frameRate;

public:
	constexpr static _ecs::id_type id = _ecs::cmp_ANIMATOR;

	Animator(GameObject* parent) : Component(parent, id){
		currentAnim = 0;
		count = 0;
		lastFrame = sdlutils().currRealTime();
		frameRate = 1000 / 60;

	};
	~Animator() {};

	void addAnimation(Texture* t, int w, int h, int n);
	void updateAnim();
};

