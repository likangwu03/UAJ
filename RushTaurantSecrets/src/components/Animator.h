#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"

using namespace std;
using Anim = std::pair<Texture*, int>;

class Animator : public Component
{
	vector<Anim> animations;

	int currentAnim;
	int count;
	float lastFrame;
	float frameRate;
	SDL_Rect sqr;

public:
	//constexpr static _ecs::id_type id = _ecs::cmp_ANIMATOR;
	constexpr static _ecs::id_type id = _ecs::cmp_TRANSFORM;

	Animator(GameObject* parent, Texture* t, const int n) : Component(parent, id){
		addAnimation(t, n);
		currentAnim = 0;
		count = 0;
		lastFrame = sdlutils().currRealTime();
		frameRate = 1000 / 60;
		sqr.x = 0;
		sqr.y = 0;
		sqr.w = 32;
		sqr.x = 32;
		cout << "anim created" << endl;
	};
	~Animator() {};

	void addAnimation(Texture* t, int n);
	void updateAnim();

	void update() {
		updateAnim();
	}
	virtual void render()
	{
		SDL_Rect temp;
		temp.x = 50;
		temp.y = 100;
		temp.w = 32;
		temp.h = 32;
		//if (!animations.empty())
		animations[currentAnim].first->render( sqr);
	};
};

