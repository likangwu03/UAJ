#pragma once
#include <vector>
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"

using namespace std;
class Animator : public Component
{
protected:
	static const int FRAMERATE = 100;
	Texture* texture;
	//fila de la anim
	int currentAnim;
	int initFrame;
	int endFrame;
	//columna de la anim
	int currFrame;
	float lastTic;
	int frameRate;

	float width;
	float height;
	//Vector pos;

	SDLUtils* sdl;
	Transform* plTf;

	float resizeFactor;
	void init(int iniFrame, int endFrame, int currAnim, int frRate,float w , float h);

	Animator(GameObject* parent, Texture* t, int iniFrame, int endFrame, int currAnim, int frRate,float w,float h,_ecs:: _cmp_id id);
	Animator(GameObject* parent, string s, int iniFrame, int endFrame, int currAnim, int frRate,float w, float h, _ecs::_cmp_id id);

public:
	//constexpr static _ecs::_cmp_id id = _ecs::cmp_ANIMATOR;

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
	
	
	/*cambiar de ancho*/
	void setW(float w) { width = w; }
	/*cambiar de alto*/
	void setH(float h) { height = h; }

	virtual void update();
	virtual void render(); //renderiza según tamaño de transform
};