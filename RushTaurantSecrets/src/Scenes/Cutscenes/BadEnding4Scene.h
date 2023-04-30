#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include "../../GameObjects/CinematicNPC.h"
#include <vector>

using namespace std;
struct dialogueInfo;

class BadEnding4Scene: public CinematicBaseScene
{
private:
	const vector<Vector> BE4PathPlayer[1] = {
		{Vector(20, 15), Vector(20, 12)}
	};

	const vector<Vector> BE4PathThief[1] = {
		{Vector(20, 15), Vector(20, 12)}
	};

	enum States {
		START,
		ARRIVE,
		D1,
		NONE
	};


	GameObject* thief;

	vector<dialogueInfo> dialogues;
	Texture* bg;
	States state;
	void addPathPantry(const vector<Vector>& points);
	vector<Vector> playerPoints;

public:
	BadEnding4Scene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};