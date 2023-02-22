#pragma once
#include "../components/TriggerComp.h"
#include "../structure/GameObject.h"

/*encargada de detectar la entrada del jugador*/
class CartelTrigger :public TriggerComp
{
public:
	CartelTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_) { }
	virtual void isOverlapping();
	virtual void onTriggerExit();
private:

};

