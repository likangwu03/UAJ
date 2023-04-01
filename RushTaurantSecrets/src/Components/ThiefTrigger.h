#pragma once
#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "ThiefState.h"
#include "ThiefMovement.h"
#include "MurderRender.h"
#include "ShooRender.h"
#include "../Structure/GameManager.h"

class ThiefTrigger : public TriggerComp
{
	ThiefState* thiefState;
	ThiefMovement* thiefMovement;
	MurderRender* mRender;
	ShooRender* sRender;

	SoundEffect* escapeSound;
	SoundEffect* dieSound;

	void hideButtons();

public:
	ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_);


	virtual void isOverlapping();
	virtual void onTriggerEnter();
	virtual void onTriggerExit();
};

