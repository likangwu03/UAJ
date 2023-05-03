#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class Day2EndingKillScene : public CinematicBaseScene {
private:
	enum States {
		INIT,
		START,
		D1,
		D2,
		D3,
		PHONE,
		PATHING,
		D4,
		D5,
		D6,
		OUT,
		NONE
	};
	Texture* bg;
	Texture* black;
	SoundEffect* phonecall;

	void addPath(const vector<Vector>& points);
	States state;

	const int START_TIME = 3;

	vector<dialogueInfo> dialogues;
	const vector<Vector> ENTERPATH = { {Vector(13, 6)} };
	const vector<Vector> PHONEPATH = { {Vector(13, 12.7)}, {Vector(11.5, 12.7)} };

public:
	Day2EndingKillScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

