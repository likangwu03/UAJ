#pragma once

#include "../scenes/UIRestaurant.h"
#include "../components/TriggerComp.h"
#include "../structure/GameObject.h"
#include "../objects/Money.h"
#include "../objects/ClientsManager.h"
#include "../components/Image.h"
/*encargada de detectar la entrada del jugador*/
class PlayerMovementController;
class Image;
class CashRegisterTrigger :public TriggerComp
{
	ClientsManager* cM;
	Money* money;
	Image* highlight;

public:
	CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_), money(Money::get()),
		cM(ClientsManager::get()),highlight(parent->getComponent<Image>()) {
		highlight->setActive(false);
	}

	virtual void isOverlapping();
	virtual void onTriggerExit();
private:

};

