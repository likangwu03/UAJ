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

	GameInfor() {};
};