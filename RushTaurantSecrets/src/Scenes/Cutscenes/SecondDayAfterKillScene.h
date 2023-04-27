
#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class SecondDayAfterKillScene : public CinematicBaseScene
{
	const vector<Vector> secondDayAfterKillPath[4] = {
		{ Vector(20, 10),Vector(16,10),Vector(18, 10)},
		{ Vector(20, 10),Vector(16,10),Vector(18, 10)},
		{ Vector(18, 14),Vector(25, 14),Vector(30,14)},
		{ Vector(40, 14)}
	};

	enum States {
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
	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;
	float cont;
	const float STOP_TIME = 1.5;

private:
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;

public:
	SecondDayAfterKillScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

