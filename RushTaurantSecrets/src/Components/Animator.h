#pragma once
#include "../Structure/Component.h"
#include "../Definitions/Structure_def.h"
#include "../Utilities/SDLUtils.h"
#include "Transform.h"
#include "../Structure/GameObject.h"

using namespace std;
class Animator : public Component
{
public:
	struct AnimParams
	{
		// primer punto de la columna
		int initFrame;
		// último punto de la columna + 1
		int endFrame;
		// fila
		int currAnim = 0;
		// velocidad de la animación
		int frameRate = FRAMERATE;
		// tamaño y ancho del sprite
		// si no se indica, se coge del transform
		float width = 0;
		float height = 0;
	};

protected:
	static const int FRAMERATE = 7;
	Texture* texture;

	//columna de la anim
	int currFrame;
	float lastTic;
	float angle;

	AnimParams animationParameters;

	SDLUtils* sdl;
	Transform* plTf;

	void init(AnimParams aP);

	Animator(GameObject* parent, Texture* t, AnimParams aP, _ecs::_cmp_id id);
	Animator(GameObject* parent, string s, AnimParams aP, _ecs::_cmp_id id);

public:
	/*mover al siguiente frame*/
	void updateAnim();
	/*cambiar de frame*/
	void setCurrentAnim(int iniFram, int endFram, int currAnim = 0);
	/*cambiar de textura dada la textura*/
	void setTexture(Texture* t, int iniFrame, int endFrame, int currAnim=0, int frRate = FRAMERATE);
	/*cambiar de textura dado el nombre de textura*/
	void setTexture(string s, int iniFrame, int endFrame, int currAnim=0, int frRate = FRAMERATE);
	/*cambiar de frameRate*/
	void setframeRate(int frRate) { animationParameters.frameRate = frRate; };
	
	
	/*cambiar de ancho*/
	void setW(float w) { animationParameters.width = w; }
	/*cambiar de alto*/
	void setH(float h) { animationParameters.height = h; }

	virtual void update();
	virtual void render(); //renderiza según tamaño de transform
};