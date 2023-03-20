#include "DayManager.h"
#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "ClientsManager.h"
#include "Reputation.h"
#include "Money.h"

#include "../utils/checkML.h"

DayManager::DayManager() : day(0) {
	// clock
	for(auto i : *GameManager::get()->getRestaurant()->getUI()->getGroup(grp_ICONS)) {
		clock = i->getComponent<ClockComponent>();
		if(clock != nullptr) break;
	}
	assert(clock != nullptr);

	// file
	file.open("assets/dayConfig.rsdat");
	if(file.fail()) throw std::exception("Data for days not found. Game cannot start.");
	nextDay();
}

void DayManager::checkDayFinished() {
	if(clock->dayHasFinished() && ClientsManager::get()->noClients()) {
		if (GameManager::get()->getReputation()->getReputation() < 0)
			GameManager::get()->setGameOver(_ecs::BadRep);
		else if (GameManager::get()->getMoney()->getMoney() < 0)
			GameManager::get()->setGameOver(_ecs::Broke);
		else GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
	}
}

int DayManager::getDay() {
	return day;
}

void DayManager::nextDay() {
	day++;
	// Leer dayConfig

}