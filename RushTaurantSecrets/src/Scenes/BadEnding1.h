#pragma once
#include "CinematicBaseScene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/CinematicNPC.h"
#include "../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class BadEnding1 : public CinematicBaseScene
{
	const float RESIZEFACTOR = 0.6666666667;

	enum States {
		START,
		ENTERING,//sonido puerta
		ARRIVE,//1
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

	GameObject* player;
	GameObject* client1;
	GameObject* client2;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;

public:
	BadEnding1();
	void callAfterCreating() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;

};

