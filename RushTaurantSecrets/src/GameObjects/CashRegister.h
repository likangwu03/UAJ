#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CashRegisterTrigger.h"
#include "../Components/Image.h"

using namespace std;
class CashRegister :public GameObject
{
private:

	const float OFFSETTRI_Y = 50;
	/*const int OFFSETW = 2;
	const int OFFSETH = -12;
	const int OFFSETY= 16;
	const int OFFSETX= 1;*/
public:
	CashRegister(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos+Vector(0,OFFSETTRI_Y), Vector(0, 0), w, h, 0, true); //para saber en donde tiene q estar el jugador para poder cobrar
		new Image(this, "CASH_HIGHLIGHT",{0,-OFFSETTRI_Y}); //renderizar el highlight
		new CashRegisterTrigger(this,Vector(0, -OFFSETTRI_Y-20),w,h);
	};
};

