#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/CashRegisterTrigger.h"

using namespace std;
class CashRegister :public GameObject
{
private:

	const int OFFSETY = -20;
public:
	CashRegister(Scene* scene, Vector pos, float w, float h) :GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h, 0, true); //para saber en donde tiene q estar el jugador para poder cobrar
		new CashRegisterTrigger(this,Vector(0, OFFSETY),w,h);
	};
};

