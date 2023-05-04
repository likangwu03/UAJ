#pragma once
#include "CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

struct dialogueInfo;
class TransitionScene;
class Day1EndingScene : public CinematicBaseScene
{
private:
	const vector<Vector> paths[2] = {
		{ Vector(12.5,14), Vector(12.5,14) },
		{ Vector(12.5,12), Vector(12.5, 5) }
	};

	enum States {
		/*INIT,*/
		START,
		ENTERING,
		D1,
		OUT,
		NONE
	};

	Texture* bg;
	Texture* filter;
	Texture* top;
	
	void addPath(const vector<Vector>& points);
	States state;

	vector<dialogueInfo> dialogues;
	vector<Vector> playerPoints;

public:
	Day1EndingScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

