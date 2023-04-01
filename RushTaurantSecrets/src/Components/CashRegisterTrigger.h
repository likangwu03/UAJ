#pragma once

#include "../Scenes/UIRestaurant.h"
#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "../Managers/Money.h"
#include "../Managers/ClientsManager.h"
#include "Image.h"
#include "../Structure/GameManager.h"
#include "Streak.h"

/*encargada de detectar la entrada del jugador*/
class PlayerMovementController;
class Image;
class CashRegisterTrigger :public TriggerComp
{
private:
	ClientsManager* cM;
	Money* money;
	Image* highlight;
	list<Client*>* list;
	Streak* streak;
	SoundEffect* cashSound1;
	SoundEffect* cashSound2;
	SoundEffect* tipSound;
	SoundEffect* addSound; //reputation
public:
	CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_);

	virtual void isOverlapping();
	virtual void onTriggerExit();
};

