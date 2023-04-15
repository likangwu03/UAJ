
#pragma once
#include "../Scenes/CinematicBaseScene.h"
#include "../GameObjects/Player.h"
#include "../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class SecondDayAfterKillScene : public CinematicBaseScene
{
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
	void callAfterCreating() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

