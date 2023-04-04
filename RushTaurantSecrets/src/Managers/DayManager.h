#pragma once
#include "../Components/ClockComponent.h"
#include "../Scenes/Restaurant.h"
#include <fstream>

class DayManager {
private:
	ClockComponent* clock;
	int day, maxDays;
	std::ifstream file;
	int dailyObjective;
	SoundEffect* timeUpSound;
	void readLine(std::string& line);
	static int to_int(std::string str);
public:
	DayManager();
	~DayManager();
	void checkDayFinished();
	int getDay();
	void nextDay();
	void setDay(int x);
	int getDailyObjective();
};