#pragma once

#include "../structure/GameObject.h"
#include "../structure/Component.h"
#include "../structure/Manager.h"

class Money : public Manager <Money> {

	friend Manager<Money>;

private:
	int amount;
	Money(GameObject* parent, int initialMoney);

public:
	static constexpr _ecs::_cmp_id id = _ecs::cmp_MONEY;

	void initMoney(int num);
	int getMoney();
	void addMoney(int num);
	void subtractMoney(int num);
};
