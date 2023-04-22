#include "DayManager.h"
#include "../structure/GameManager.h"
#include "ClientsManager.h"
#include "Reputation.h"
#include "Money.h"

#include "../Scenes/GameScenes/EndOfDayScene.h"
#include "../Scenes/Cutscenes/FirstDayAfterKillScene.h"
#include "../Scenes/Cutscenes/SecondDayAfterKillScene.h"
#include "../Scenes/Cutscenes/BadEnding1Scene.h"

#include "../Utilities/checkML.h"

void DayManager::readLine(std::string & line) {
	do {
		std::getline(file, line);
		while (!line.empty() && line[0] == '\t') line = line.substr(1);
	} while (!file.eof() && (line.empty() || line[0] == '#')); // Si la línea que se lee est?vacía o es un comentario (empieza con '#'), se lee la siguiente.
	if (file.eof()) { line = ""; }
}

int DayManager::to_int(std::string str) {
	int i = 0;

	for (auto& ch : str) {
		if (ch < '0' || ch > '9') return -1;
		i = i * 10 + ch - '0';
	}

	return i;
}

float DayManager::to_float(std::string str) {
	int i = 0; float j = 0;
	bool decimal = false;

	for (auto& ch : str) {
		if (ch < '0' || ch > '9') {
			if (!decimal && ch != '.') return -1;
			decimal = true;
		}
		else if (decimal) {
			j = j * 10 + ch - '0';
		}
		else {
			i = i * 10 + ch - '0';
		}
	}
	while (j >= 1) j /= 10;

	return i + j;
}

DayManager::DayManager() : day(0), timeUpSound(&sdlutils().soundEffects().at("TIME_UP")),
sdl(SDLUtils::instance()), restaurantMusic(&sdl->musics().at("RESTAURANT_MUSIC"))
{
	// file
	file.open("assets/dayConfig.rsdat");
	if (file.fail()) throw std::exception("Data for days not found.\n");
	file >> maxDays;
	restaurantMusic->setMusicVolume(MUSIC_VOL);

#ifdef _DEBUG
	std::cout << "DayManager initiated.\n";
#endif // _DEBUG
}

DayManager::~DayManager() {
	if (file.is_open()) file.close();
}

void DayManager::checkDayFinished() {

	if (ClockComponent::get()->dayHasFinished() && ClientsManager::get()->noClients()) {
		if (GameManager::get()->getReputation()->getReputation() < 0)

			GameManager::get()->setGameOver(_ecs::BadRep);
		else if (GameManager::get()->getMoney()->getMoney() < 0)
			GameManager::get()->setGameOver(_ecs::Broke);
		else {
			GameManager::get()->save();
			GameManager::get()->changeScene((Scene*)GameManager::get()->getEndOfDay());
		}
	}
}

void DayManager::newDay() {
	restaurantMusic->pauseMusic();
	timeUpSound->play();
	nextDay();
}

void DayManager::nextDay(bool loadingGame) {
	day++;

	if (day > maxDays) {
		// Activar final, ya que no hay más días

		return;
	}

	if (GameManager::get()->getReputation() < 0) {
		GameManager::get()->changeScene(GameManager::get()->getBadEnding1Scene(), true);
		GameManager::get()->getBadEnding1Scene()->callAfterCreating();
	}

	if (GameManager::get()->getHasEverKilled().first) {
		if (day - GameManager::get()->getHasEverKilled().second == 1)
		{
			GameManager::get()->changeScene(GameManager::get()->getFirstDayAfterKillScene(), true);
			GameManager::get()->getFirstDayAfterKillScene()->callAfterCreating();
		}
		else if (day - GameManager::get()->getHasEverKilled().second == 2)
		{
			GameManager::get()->changeScene(GameManager::get()->getSecondDayAfterKillScene(), true);
			GameManager::get()->getSecondDayAfterKillScene()->callAfterCreating();
		}
	}
	else if(!loadingGame) GameManager::get()->changeScene((Scene*)GameManager::get()->getBeforeDayStart());


	// Leer dayConfig
	std::string line = "";
	while (!file.eof() && line != "begin") {
		readLine(line);
	}

	while (!file.eof() && line != "end") {
		readLine(line);

		// Recoger los parámetros de este día
		if (line.substr(0, 9) == "objective") {
			dailyObjective = to_int(line.substr(10));
		}
		else if (line.substr(0, 15) == "clientFrequency") {
			clientFrequency = to_float(line.substr(16));
		}
		else if (line.substr(0, 18) == "happinessFrequency") {
			happinessFrequency = to_float(line.substr(19));
		}
		else if (line.substr(0, 18) == "reputationDecrease") {
			reputationDecrease = to_float(line.substr(19));
		}
		else if (line.substr(0, 21) == "minimumThiefFrequency") {
			minimumThiefFrequency = to_float(line.substr(22));
		}
		else if (line.substr(0, 21) == "maximumThiefFrequency") {
			maximumThiefFrequency = to_float(line.substr(22));
		}
	}

	GameManager::get()->resetScenes();
}

void DayManager::setDay(int x) {
	if (file.is_open()) file.close();

	file.open("assets/dayConfig.rsdat");
	if (file.fail()) throw std::exception("Data for days not found.\n");
	file >> maxDays;

	string line = "";
	for (int i = 0; i < x - 1; i++) {
		while (!file.eof() && line != "end") {
			readLine(line);
		}
	}
	day = x - 1;
	nextDay(true);
}

int DayManager::getDay() { return day; }
int DayManager::getDailyObjective() { return dailyObjective; }
float DayManager::getClientFrequency() { return clientFrequency; }
float DayManager::getHappinessFrequency() { return happinessFrequency; }
float DayManager::getReputationDecrease() { return reputationDecrease; }
float DayManager::getMinThiefFrequency() { return minimumThiefFrequency; }
float DayManager::getMaxThiefFrequency() { return maximumThiefFrequency; }