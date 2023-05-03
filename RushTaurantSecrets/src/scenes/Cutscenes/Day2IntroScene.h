#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class TransitionScene;
class Day2IntroScene : public CinematicBaseScene
{
	const vector<Vector> paths[3] = {
		{Vector(5.5, 1)},
		{Vector(12.5, 1)},
		{Vector(12.5, 12), Vector(11, 12)}
	};

	enum States {
		START,
		ENTERING, //suena telefono
		ARRIVE, //camino a telefono
		D1, //contesta telefono
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		D8,
		D9,
		D10,
		D11,
		D12,
		D13,
		OUT,
		NONE
	};

	Texture* bg;
	Texture* top;
	Texture* black;
	SoundEffect* phonecall;
	Music* dayMusic;

	void addPath(const vector<Vector>& points);
	States state;

	vector<dialogueInfo> dialogues;

public:
	Day2IntroScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

