#include "FinishDay.h"
#include "../scenes/Restaurant.h"
#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "../objects/ClientsManager.h"

FinishDay::FinishDay(GameObject* parent) : Component(parent, id), clock(nullptr) { }

void FinishDay::update() {
	/*if(ui->dayHasFinished()) cout << "Day has finished";
	if(ui->dayHasFinished() && ClientsManager::get()->noClients()) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
	}*/
}

void FinishDay::initComponent() {
	for(auto i : *GameManager::get()->getRestaurant()->getUI()->getGroup(grp_ICONS)) {
		clock = i->getComponent<ClockComponent>();
		if(clock != nullptr) break;
	}
	//clock = GameManager::get()->getRestaurant()->getUI()->getGameObject(hdr_CLOCK)->getComponent<ClockComponent>();
	assert(clock != nullptr);
}