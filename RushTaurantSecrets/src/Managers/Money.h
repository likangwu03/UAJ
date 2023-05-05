#pragma once

#include "../Definitions/Structure_def.h"

class Money {
private:
	const int BASEANMOUNT = 200;
	int initialAmount, amount;
	int price = 0;
public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_MONEY;
	Money() { amount = initialAmount = BASEANMOUNT; }

	int getMoney() { return amount; }
	void addMoney(int num) { amount += num; }
	void subtractMoney(int num) { amount -= num; }
	void setPrice(int num) { price = num; }
	int getPrice() { return price; }
	void newGame() { amount = initialAmount = BASEANMOUNT; }
	int getEarnedMoney() { return (amount - initialAmount); }
	void reset() { initialAmount = amount; }
};
