#pragma once

#include "../Utilities/SDLUtils.h"
#include "../Definitions/Structure_def.h"
class Reputation {
	const int INITIALREPUTATION = 15, MAXREPUTATION = 100;
	float amount;

	SoundEffect* decreaseSound;
public:
	Reputation() : amount(INITIALREPUTATION), 
		decreaseSound(&sdlutils().soundEffects().at("LOSE_REPUTATION"))
	{ }

	float getReputation() { return amount; }
	void addReputatiton(float n) {
		amount += n;
		if (amount > MAXREPUTATION) amount = MAXREPUTATION;
	}
	void reduceReputation(float n) { 
		amount -= n; 
		decreaseSound->play();
	}
};
