#pragma once
#include "../components/ClockComponent.h"
#include "../scenes/Restaurant.h"
#include <fstream>

class DayManager {
private:
	ClockComponent* clock;
	int day, maxDays;
	std::ifstream file;
	int dailyObjective;

	void readLine(std::string& line);
public:
	DayManager();
	~DayManager();
	void checkDayFinished();
	int getDay();
	void nextDay();

	int getDailyObjective();
};