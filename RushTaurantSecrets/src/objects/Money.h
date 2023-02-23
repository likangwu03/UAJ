#pragma once

class Money {
private:
	//Money();
	//static Money* instance;
	int amount;

public:
	/*static Money* Instance() {
		if (instance == nullptr) {
			instance = new Money();
			instance->initMoney(0);
		}
		return instance;
	}*/

	Money();
	void initMoney(int num);
	int getMoney();
	void addMoney(int num);
	void subtractMoney(int num);
};
