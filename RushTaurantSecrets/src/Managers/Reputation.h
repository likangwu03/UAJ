#pragma once


class Reputation {
	const int INITIALREPUTATION = 15, MAXREPUTATION = 100;
	float amount;

public:
	Reputation() : amount(INITIALREPUTATION) { }

	float getReputation() { return amount; }
	void addReputatiton(float n) {
		amount += n;
		if (amount > MAXREPUTATION) amount = MAXREPUTATION;
	}
	void reduceReputation(float n) { amount -= n; }
};
