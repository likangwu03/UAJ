#pragma once

#include "../scenes/UIRestaurant.h"
#include "../components/TriggerComp.h"
#include "../structure/GameObject.h"
#include "../objects/Money.h"
#include "../objects/ClientsManager.h"
#include "../components/Image.h"
#include "../structure/GameManager.h"
#include "../components/Streak.h"

/*encargada de detectar la entrada del jugador*/
class PlayerMovementController;
class Image;
class CashRegisterTrigger :public TriggerComp
{
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
private:

};

