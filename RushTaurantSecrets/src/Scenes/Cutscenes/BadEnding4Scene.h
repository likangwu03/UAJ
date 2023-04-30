#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include "../../GameObjects/CinematicNPC.h"
#include "../../GameObjects/CinematicObject.h"
#include <vector>

using namespace std;
struct dialogueInfo;

class BadEnding4Scene: public CinematicBaseScene
{
private:
	const vector<Vector> BE4PathPlayer[1] = {
		{Vector(20, 14), Vector(20, 12)}
	};
	const vector<Vector> BE4PathThief[4] = {
		{Vector(23, 5)}, {Vector(7, 5)}, {Vector(7, 12)}, {Vector(-2, 12)}
	};

	enum States {
		START,
		D1,
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
		D15,
		D16,
		D17,
		D18,
		D19,
		D21,
		D22,
		D23,
		D24,
		D25,
		D26,
		D27,
		D28,
		D29,
		D30,
		D31,
		D32,
		D33,
		D34,
		D35,
		D36,
		D37,
		D38,
		D39,
		D40,
		D41,
		D42,
		D43,
		D44,
		D45,
		NONE
	};

	GameObject* thief;
	GameObject* book;

	vector<dialogueInfo> dialogues;
	Texture* bg;
	Texture* top;
	States state;
	void addPathPantry(const vector<Vector>& points);
	vector<Vector> playerPoints;
	StraightMovement* straightMovementThief;
	bool reading;

public:
	BadEnding4Scene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};