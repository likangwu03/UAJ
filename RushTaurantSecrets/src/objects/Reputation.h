#pragma once

#include "../utils/Singleton.h"
#include "../utils/checkML.h"

class Reputation : public Singleton<Reputation> {
	friend Singleton<Reputation>; private:

	float amount;
	const int MAXREPUTATION = 100;
	Reputation() { amount = 15; }

public:
	float getReputation() { return amount; }
	void addReputatiton(float n) {
		amount += n;
		if (amount > MAXREPUTATION) amount = MAXREPUTATION;
	}
	void reduceReputation(float n) { amount -= n; }
};
