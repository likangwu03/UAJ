#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include "../../GameObjects/CinematicNPC.h"
#include <vector>

using namespace std;
struct dialogueInfo;

class BadEnding4Scene: public CinematicBaseScene
{
private:
	const vector<Vector> BE4PathPlayer[6] = {
		//{Vector(20, 14)}, 
		{Vector(20, 12)}, 
		//{Vector(20, 20)}, {Vector(23, 8)}, 
		{Vector(21, 7), Vector(21, 5)}
	};
	const vector<Vector> BE4PathThief[2] = {
		{Vector(23, 5)},
		{Vector(7, 5), Vector(7, 12), Vector(-2, 12)}
	};

	enum States {
		START,
		D1,
		D2,
		D3,
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
		D20,
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
		D37,
		D38,
		D39,
		D40,
		D41,
		D42,
		D43,
		D44,
		D45,
		D46,
		D47,
		D48,
		D49,
		D50,
		LAST,
		NONE
	};

	GameObject* thief;
	GameObject* book;

	vector<dialogueInfo> dialogues;
	Texture* bg;
	Texture* top;
	Texture* filter;
	Texture* tvFilter;
	Texture* lectern;
	Texture* black;
	States state;
	void addPathPantry(const vector<Vector>& points);
	StraightMovement* straightMovementThief;
	bool reading, night, stolenBook;
	Music* pantryMusic;
	Music* homeMusic;
	SoundEffect* warningSound;

public:
	BadEnding4Scene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};