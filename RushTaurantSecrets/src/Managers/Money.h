#pragma once

#include "../Definitions/Structure_def.h"

class Money {
private:
	const int INITIALANMOUNT = 200;
	int amount;
	int prize = 0;
public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_MONEY;
	Money() : amount(INITIALANMOUNT) { }

	int getMoney() { return amount; }
	void addMoney(int num) { amount += num; }
	void subtractMoney(int num) { amount -= num; }
	void setPrize(int num) { prize = num; }
	int getPrize() { return prize; }
	void newGame() { amount = INITIALANMOUNT; }
	int getEarnedMoney() { return (INITIALANMOUNT - amount); }
};
