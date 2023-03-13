#pragma once

#include "../utils/Singleton.h"

#include "../objects/Reputation.h"
#include "../objects/Money.h"
#include "../scenes/Restaurant.h"
#include "../scenes/Pantry.h"
#include "../scenes/SuperMarket.h"
#include "../gameObjects/Player.h"

class GameManager:public Singleton<GameManager> {
	friend Singleton<GameManager>;

public:
	GameManager(GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;

	Player* player;

	Reputation* reputation;
	Money* money;

	Restaurant* restaurant;
	Pantry* pantry;
	SuperMarket* supermarket;

private:
	bool hasKilled;


	GameManager(): hasKilled(false), money(0), reputation() { };

public:
	bool& getHasKill() { return hasKilled; }
	void setHasKill(bool hKill) { hasKilled = hKill; }
};