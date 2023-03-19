#include "FinishDay.h"
#include "../scenes/Restaurant.h"
#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "../objects/ClientsManager.h"
#include "../objects/Reputation.h"
#include "../objects/Money.h"

#include "../utils/checkML.h"

FinishDay::FinishDay(GameObject* parent) : Component(parent, id), clock(nullptr) { }

void FinishDay::update() {
	if(clock->dayHasFinished() && ClientsManager::get()->noClients()) {
		if (GameManager::get()->getReputation()->getReputation() < 0)
			GameManager::get()->setGameOver(_ecs::BadRep);
		else if (GameManager::get()->getMoney()->getMoney() < 0)
			GameManager::get()->setGameOver(_ecs::Broke);
		else GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
	}
}

void FinishDay::initComponent() {
	for(auto i : *GameManager::get()->getRestaurant()->getUI()->getGroup(grp_ICONS)) {
		clock = i->getComponent<ClockComponent>();
		if(clock != nullptr) break;
	}
	//clock = GameManager::get()->getRestaurant()->getUI()->getGameObject(hdr_CLOCK)->getComponent<ClockComponent>();
	assert(clock != nullptr);
}