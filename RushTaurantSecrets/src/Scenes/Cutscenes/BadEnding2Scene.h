#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;

class EndingDay2NoKillScene : public CinematicBaseScene {
private:
	const int TURNAROUNDTIME = 500;
	const Vector BOXPOS = Vector(150, 20);
	const float BOXW = 700, LETTERFREQ = 0.01f * 1000;

	const vector<Vector> paths[1] = {
		{ Vector(19.5, 25), Vector(19.5, 15) }
	};

	enum States {
		START,
		TURN1,
		TURN2,
		D1DELAY,
		D1,
		D2,
		D3,
		OUT,
		NONE
	};

	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;
	
	Texture* filter;
	Texture* bg;
	SoundEffect* nightAmbience;
	Music* nightMusic;

	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;
	int timer;
	int dialogueN;

public:
	EndingDay2NoKillScene();
	void callAfterCreating() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

