#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class FirstDayAfterKillScene : public CinematicBaseScene
{
private:
	enum States {
		INIT,
		START,
		M1,
		P1,
		M2,
		P2,
		MOV1,
		M3,
		M4,
		P3,
		BACKUP,
		M5,
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
	const float START_TIME = 3;

	vector<dialogueInfo> dialogues;

public:
	FirstDayAfterKillScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

