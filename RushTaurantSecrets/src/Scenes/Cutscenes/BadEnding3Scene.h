#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"

#include <vector>

using namespace std;
struct dialogueInfo;
class CinematicNPC;

class BadEnding3Scene : public CinematicBaseScene {
private:
	const int DELAY = 1000;
	const Vector BOXPOS = Vector(150, 20);
	const float BOXW = 700, LETTERFREQ = 0.01f * 1000;

	const float PANTRYSIZE = 0.8333333333;

	const vector<Vector> paths[2] = {
		{ Vector(19.5, 19), Vector(19.5, 14) },
		{ Vector(19.5, 14), Vector(15, 14), Vector(15, 14), Vector(15,7), Vector(10,7), Vector(10,8),  Vector(6,8), Vector(6,12) }
	};
	const vector<Vector> thiefPaths[3] = {
		{ Vector(15, 6), Vector(15,7) },
		{ Vector(15,7), Vector(10,7) },
		{ Vector(10,7), Vector(10,8),  Vector(6,8), Vector(6,12), Vector(-1,12) }
	};
	const vector<Vector> policePaths[1] = {
		{ Vector(-1,12), Vector(4,12) }
	};


	enum States {
		INIT,
		START,
		WALK,
		ENTER,
		D2,
		D3,
		D4,
		RUN,
		FALL,
		GETUP,
		GETOUT,
		D5,
		D6,
		D7,
		GUN,
		D8,
		D9,
		D10,
		D11,
		D12,
		D13,
		D14,

		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points, GameObject* object);
	States state;
	
	Texture* bg;
	Texture* black;
	Texture* top;


	Music* music;
	SoundEffect* siren;

	GameObject* thief;
	GameObject* police;

	vector<dialogueInfo> dialogues;
	int timer;
	int dialogueN;
	int musicVol;



public:
	BadEnding3Scene();
	void reset() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;

};

