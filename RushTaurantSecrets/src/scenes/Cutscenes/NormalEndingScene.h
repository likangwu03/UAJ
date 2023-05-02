#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class NormalEndingScene : public CinematicBaseScene
{
private:
	const int CARCRUSH_TIMER = 9;
	const int BEEP_TIMER = 2;
	const int FINISH_TIMER = 5;

	const vector<Vector> path[8] = {
		{Vector(13, 13)}, // ENTERING
		{Vector(13, 5), Vector(6, 5), Vector(6, 4)}, //ROOM
		{Vector(2, 4), Vector(6, 4)}, //MOVE
		{Vector(6, 5)}, //MOVE2
		{Vector(6, 2)}, //MOVE3
		{Vector(5, 2), Vector(5, 1)}, //MOVE4
		{Vector(5, 5), Vector(12, 5), Vector(12, 13)}, //OUTSIDE
		{Vector(12, 16)} //OUT
	};

	enum States {
		START,
		ENTERING,//sonido puerta
		D1,
		ROOM,
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
		D14,
		MOVE,
		D15,
		MOVE2,
		D16,
		D17,
		D18,
		MOVE3,
		D19,
		MOVE4,
		D20,
		OUTSIDE,
		D21,
		D22,
		D23,
		BRBKMS,
		CARCRASH,
		BEEP,
		WAITCARCRASH,
		OUT,
		NONE
	};

	Texture* bg;
	Texture* top;
	Texture* black;
	Music* creepyMusic;

	void addPath(const vector<Vector>& points);
	States state;

	vector<dialogueInfo> dialogues;

public:
	NormalEndingScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

