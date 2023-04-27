#pragma once

#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;

class IntroDay3ScareScene : public CinematicBaseScene
{
	int THUNDER_TIMER = 5;
	const vector<Vector> playerPaths[2] = {
	{Vector(40, 14), Vector(28, 14)},
	{Vector(18, 14),Vector(18,10)}
	};

	enum States {
		START,
		ENTERING,//sonido puerta
		ARRIVE,//1
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		OUT,
		NONE
	};

	Texture* bg;
	Texture* filter;
	Texture* top;
	Texture* black;
	SoundEffect* rainAmbience;
	Music* creepyMusic;
	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;

private:
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;

public:
	IntroDay3ScareScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

