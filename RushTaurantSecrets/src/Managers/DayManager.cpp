#include "DayManager.h"
#include "../scenes/UIRestaurant.h"
#include "../structure/GameManager.h"
#include "ClientsManager.h"
#include "Reputation.h"
#include "Money.h"

#include "../Utilities/checkML.h"

void DayManager::readLine(std::string& line) {
	do {
		std::getline(file, line);
		while(!line.empty() && line[0] == '\t') line = line.substr(1);
	} while(!file.eof() && (line.empty() || line[0] == '#')); // Si la línea que se lee está vacía o es un comentario (empieza con '#'), se lee la siguiente.
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

DayManager::DayManager() : day(0) {
	// clock
	for(auto i : *GameManager::get()->getRestaurant()->getUI()->getGroup(grp_ICONS)) {
		clock = i->getComponent<ClockComponent>();
		if(clock != nullptr) break;
	}
	assert(clock != nullptr);

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
	if(clock->dayHasFinished() && ClientsManager::get()->noClients()) {
		/*if(GameManager::get()->getReputation()->getReputation() < 0)
			GameManager::get()->setGameOver(_ecs::BadRep);
		else if (GameManager::get()->getMoney()->getMoney() < 0)
			GameManager::get()->setGameOver(_ecs::Broke);
		else*/ {
			nextDay();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getDailyMenu());
		}
	}
}

int DayManager::getDay() { return day; }

void DayManager::nextDay() {
	day++;
	GameManager::get()->getRestaurant()->nextDay();

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