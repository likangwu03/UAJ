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
	const vector<Vector> BE4Path[1] = {
		{Vector(20, 15), Vector(20, 14)}
	};

	enum States {
		START,
		NONE
	};

private:
	GameObject* player;
	GameObject* thief;
	StraightMovement* straightMovement;
	vector<dialogueInfo> dialogues;
	Texture* bg;
	States state;
	void addPathPantry(const vector<Vector>& points);

public:
	BadEnding4Scene();
	void callAfterCreating() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};