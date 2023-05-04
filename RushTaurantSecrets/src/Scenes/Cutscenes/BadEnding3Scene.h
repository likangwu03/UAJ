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


	const vector<Vector> paths[7] = {

	};

	enum States {
		INIT,
		START,
		D1,

		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points);
	States state;
	
	Texture* bg;
	Texture* black;
	Texture* top;


	Music* music;
	SoundEffect* phonecall;

	GameObject* thief;

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

