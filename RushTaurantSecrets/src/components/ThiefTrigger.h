#pragma once
#include "../components/TriggerComp.h"
#include "../structure/GameObject.h"
#include "../components/ThiefMovement.h"
#include "../components/MurderRender.h"
#include "../components/ShooRender.h"

class ThiefTrigger : public TriggerComp
{
	ThiefMovement* tMovement;
	MurderRender* mRender;
	ShooRender* sRender;
public:
	ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();
	virtual void onTriggerEnter();
	virtual void onTriggerExit();
};

