#pragma once

#include "../structure/Structure_def.h"

class Money {
private:
	const int INITIALANMOUNT = 200;
	int amount;

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_MONEY;
	Money() : amount(INITIALANMOUNT) { }

	int getMoney() { return amount; }
	void addMoney(int num) { amount += num; }
	void subtractMoney(int num) { amount -= num; }
};
