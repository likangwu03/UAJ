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

public:
	CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_) :
		TriggerComp(parent, pos_, width_, height_), money(GameManager::get()->getMoney()),
		cM(ClientsManager::get()), highlight(parent->getComponent<Image>()) {

		highlight->setActive(false);
		list = cM->getPayQueue();
		streak = GameManager::get()->getRestaurant()->getUI()->getGameObject(_ecs::hdr_STREAK)->getComponent<Streak>();
	}

	virtual void isOverlapping();
	virtual void onTriggerExit();
};

