
#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class SecondDayAfterKillScene : public CinematicBaseScene
{
private:
	const vector<Vector> secondDayAfterKillPath[5] = {
		{ Vector(20, 10) },
		{ Vector(18, 10) },
		{ Vector(20, 10),Vector(16,10),Vector(18, 10)},
		{ Vector(18, 14),Vector(25, 14),Vector(30,14)},
		{ Vector(40, 14)}
	};

	enum States {
		MUSIC,
		START,
		PAUSE,
		START2,
		M1,
		M2,
		P1,
		M3,
		P2,
		M4,
		P3,
		WALKING,
		M5,
		M6,
		M7,
		OUT,
		NONE
	};
	Texture* bg;
	Texture* filter;
	Texture* top;
	SoundEffect* nightAmbience;
	Music* nightMusic;
	void addPath(const vector<Vector>& points);
	States state;
	float cont;
	const float STOP_TIME = 1.5;

	vector<dialogueInfo> dialogues;

public:
	SecondDayAfterKillScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

