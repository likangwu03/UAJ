#pragma once
#include "../Components/ClockComponent.h"
#include "../Scenes/GameScenes/Restaurant.h"
#include <fstream>

class DayManager {
private:
	const int MUSIC_VOL = 30;

	int day, maxDays;
	std::ifstream file;
	int dailyObjective;
	float clientFrequency, happinessFrequency, reputationDecrease, minimumThiefFrequency, maximumThiefFrequency;
	SoundEffect* timeUpSound;
	void readLine(std::string& line);
	static int to_int(std::string str);
	static float to_float(std::string str);

	SDLUtils* sdl;
	Music* restaurantMusic;
public:
	DayManager();
	~DayManager();
	void checkDayFinished();
	void nextDay(bool loadingGame = false);
	void setDay(int x);
	void newDay();

	SoundEffect* getSound() { return timeUpSound; }

	int getDay();
	int getDailyObjective();
	float getClientFrequency();
	float getHappinessFrequency();
	float getReputationDecrease();
	float getMinThiefFrequency();
	float getMaxThiefFrequency();
};