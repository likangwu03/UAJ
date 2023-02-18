#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"
#include "../sdlutils/Texture.h"
#include "../components/PlayerMovementController.h"
using namespace std;
class Animator : public Component
{
	static const int FRAMERATE = 100;
private:
	Texture* texture;
	bool able;
	//fila de la anim
	int currentAnim;
	int initFrame;
	int endFrame;
	//columna de la anim
	int currFrame;
	float lastTic;
	int frameRate;
	SDLUtils* sdl;
	GOOrientation parentOrientation;
	GOOrientation currOrientation;

	Transform* plTf;
	PlayerMovementController* plMov;

	float resizeFactor;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_ANIMATOR;

	Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim, int frRate = FRAMERATE);
	Animator(GameObject* parent, string s, int iniFrame, int endFrame, int currAnim, int frRate = FRAMERATE);
	
	/*mover al siguiente frame*/
	void updateAnim();
	/*cambiar de frame*/
	void setCurrentAnim(int iniFram, int endFram, int currAnim = 0);
	/*cambiar de textura dada la textura*/
	void setTexture(Texture* t, int iniFrame, int endFrame, int currAnim, int frRate = FRAMERATE);
	/*cambiar de textura dado el nombre de textura*/
	void setTexture(string s, int iniFrame, int endFrame, int currAnim, int frRate = FRAMERATE);
	/*cambiar de frameRate*/
	void setframeRate(int frRate) { frameRate = frRate; };
	/*cambiar si se puede renderizar y acutalizar*/
	void setAble(bool b);

	virtual void update();
	virtual void render();
};