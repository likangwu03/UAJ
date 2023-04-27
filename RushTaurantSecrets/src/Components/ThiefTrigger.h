#pragma once
#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "../Structure/GameManager.h"
#include "ThiefState.h"
#include "ThiefMovement.h"
#include "ShowControlAuto.h"

class ThiefTrigger : public TriggerComp
{
	//CONTROLES ARRIBA
	const float RUN_X_OFFSET = 0,
				KILL_X_OFFSET = 40,
				RUN_Y_OFFSET = 10,
				KILL_Y_OFFSET  = 10,
				WIDTH = 30, HEIGHT = 30;

	//CONTROLES A LOS LADOS
	//const float KILL_X_OFFSET = 48,
	//	KILL_Y_OFFSET = 35,
	//	RUN_Y_OFFSET = 67,
	//	WIDTH = 30, HEIGHT = 30;

	Transform* parentTransform;
	ThiefState* thiefState;
	ThiefMovement* thiefMovement;
	ShowControlComp* showControl;

	Texture* runTexture;
	Texture* killTexture;

	SoundEffect* escapeSound;
	SoundEffect* dieSound;


	void hideButtons();

public:
	ThiefTrigger(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();
	virtual void onTriggerEnter();
	virtual void onTriggerExit();
	virtual void render();
};

