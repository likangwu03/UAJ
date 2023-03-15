#include "FinishDay.h"
#include "../scenes/Restaurant.h"
#include "../structure/GameManager.h"
#include "../objects/ClientsManager.h"

FinishDay::FinishDay(GameObject* parent) : Component(parent, id), ui(GameManager::get()->getRestaurant()->getUI()) { }

void FinishDay::update() {
	if(ui->dayHasFinished()) cout << "Day has finished";
	if(ui->dayHasFinished() && ClientsManager::get()->noClients()) {
		GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
	}
}