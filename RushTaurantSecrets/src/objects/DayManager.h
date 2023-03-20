#pragma once
#include "../components/ClockComponent.h"
#include "../scenes/Restaurant.h"
#include <fstream>

class DayManager {
private:
	ClockComponent* clock;
	int day;
	std::ifstream file;
public:
	DayManager();
	void checkDayFinished();
	int getDay();
	void nextDay();
};