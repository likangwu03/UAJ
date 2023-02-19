#pragma once

#include "../scenes/UIRestaurant.h"
#include "../components/TriggerComp.h"
#include "../structure/GameObject.h"
#include "../objects/Money.h"
#include "../objects/ClientsManager.h"

/*encargada de detectar la entrada del jugador*/
class PlayerMovementController;
class CashRegisterTrigger :public TriggerComp
{
	ClientsManager* cM;
	Money* money;
public:
	CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_),money(static_cast<UIRestaurant*>(parent->getScene()->getUI())->getMoney()),
		cM(ClientsManager::get()) { }

	virtual void isOverlapping();
private:

};

