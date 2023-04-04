#include "DayManager.h"
#include <sstream>
#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "ClientsManager.h"
#include "Reputation.h"
#include "Money.h"
#include "../scenes/DailyMenuScene.h"
#include "../Scenes/BeforeDayStartScene.h"
#include "../Utilities/checkML.h"

void DayManager::readLine(std::string& line) {
	do {
		std::getline(file, line);
		while(!line.empty() && line[0] == '\t') line = line.substr(1);
	} while(!file.eof() && (line.empty() || line[0] == '#')); // Si la línea que se lee est?vacía o es un comentario (empieza con '#'), se lee la siguiente.
	if(file.eof()) { line = ""; }
}

int DayManager::to_int(std::string str) {
	int i = 0;

	for(auto& ch : str) {
		if(ch < '0' || ch > '9') return -1;
		i = i * 10 + ch - '0';
	}

	return i;
}

DayManager::DayManager() : day(0), timeUpSound(&sdlutils().soundEffects().at("TIME_UP")) {
	// file
	file.open("assets/dayConfig.rsdat");
	if(file.fail()) throw std::exception("Data for days not found.\n");
	file >> maxDays;
	nextDay();

#ifdef _DEBUG
	std::cout << "DayManager initiated.\n";
#endif // _DEBUG
}

DayManager::~DayManager() {
	if(file.is_open()) file.close();
}

void DayManager::checkDayFinished() {
	if(ClockComponent::get()->dayHasFinished() && ClientsManager::get()->noClients()) {
		/*if(GameManager::get()->getReputation()->getReputation() < 0)
			GameManager::get()->setGameOver(_ecs::BadRep);
		else if (GameManager::get()->getMoney()->getMoney() < 0)
			GameManager::get()->setGameOver(_ecs::Broke);
		else*/ {
			nextDay();
			GameManager::get()->save();
			GameManager::get()->getDailyMenu()->reset();
			GameManager::get()->getBeforeDayStart()->reset();
			//GameManager::get()->getBeforeDayStart()->init();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getBeforeDayStart());
			timeUpSound->play();
		}
	}
}

int DayManager::getDay() { return day; }

void DayManager::nextDay() {
	day++;
	GameManager::get()->getRestaurant()->nextDay();
	GameManager::get()->getRestaurant()->getUI()->nextDay();
	GameManager::get()->getPantry()->nextDay();

	if(day > maxDays) {
		// Activar final, ya que no hay más días

		return;
	}

	// Leer dayConfig

	std::string line;
	while(!file.eof() && line != "begin") {
		readLine(line);
	}

	while(!file.eof() && line != "end") {
		readLine(line);

		// Recoger los parámetros de este día
		if(line.substr(0, 9) == "objective") {
			dailyObjective = to_int(line.substr(10));
		}
	}
}

int DayManager::getDailyObjective() { return dailyObjective; }


void DayManager::setDay(int x) {
	if (file.is_open()) file.close();

	file.open("assets/dayConfig.rsdat");
	if (file.fail()) throw std::exception("Data for days not found.\n");
	file >> maxDays;

	string line;
	stringstream d;
	d << "# Día " << x ;
	std::getline(file, line);
	while (!file.eof() && line != d.str()) {
		std::getline(file, line);
	}
	day = x-1;
	nextDay();
}