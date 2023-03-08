#pragma once
#include "../utils/Singleton.h"
class GameInfor:public Singleton<GameInfor> {
	friend Singleton<GameInfor>;
public:
	GameInfor(GameInfor&) = delete;
	GameInfor(GameInfor&&) = delete;
	GameInfor& operator=(GameInfor&) = delete;
	GameInfor& operator=(GameInfor&&) = delete;

private:
	bool hasKill;
	int money;
	int reputation;

	
	GameInfor(): hasKill(false), money(0), reputation(20) { };
public:
	int& getMoney() { return money; }
	int& getReputation() { return reputation; }
	bool& getHasKill() { return hasKill; }
	void setHasKill(bool hKill) { hasKill = hKill; }
};