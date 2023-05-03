#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;

class Day2EndingNoKillScene : public CinematicBaseScene {
private:
	const int TURNAROUNDTIME = 500;
	const Vector BOXPOS = Vector(150, 20);
	const float BOXW = 700, LETTERFREQ = 0.01f * 1000;

	const Animator::AnimParams AP = { 18,18,1 };

	const vector<Vector> paths[2] = {
		{ Vector(19.5, 25), Vector(19.5, 22) },
		{ Vector(19.5, 21), Vector(19.5, 15) }
	};

	enum States {
		INIT,
		START,
		ENTERING,
		TURN,
		D1DELAY,
		D1,
		D2,
		D3,
		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points);
	States state;
	
	Texture* filter;
	Texture* bg;
	SoundEffect* nightAmbience;
	Music* nightMusic;

	vector<dialogueInfo> dialogues;
	int timer;
	int dialogueN;

public:
	Day2EndingNoKillScene();
	void reset() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

