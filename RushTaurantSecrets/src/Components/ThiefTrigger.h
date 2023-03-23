#pragma once
#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "ThiefMovement.h"
#include "MurderRender.h"
#include "ShooRender.h"
#include "../Structure/GameManager.h"

class ThiefTrigger : public TriggerComp
{
	ThiefMovement* tMovement;
	MurderRender* mRender;
	ShooRender* sRender;
public:
	ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_);

	void killPressed();

	virtual void isOverlapping();
	virtual void onTriggerEnter();
	virtual void onTriggerExit();
};

