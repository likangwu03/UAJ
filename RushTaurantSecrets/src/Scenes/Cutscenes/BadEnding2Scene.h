#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"

#include <vector>

using namespace std;
struct dialogueInfo;
class CinematicNPC;

class BadEnding2Scene : public CinematicBaseScene {
private:
	const int DELAY = 1000;
	const Vector BOXPOS = Vector(150, 20);
	const float BOXW = 700, LETTERFREQ = 0.01f * 1000;

	const float RESTSIZE = 0.6666666667;


	const vector<Vector> paths[6] = {
		{ Vector(8.8, 2), Vector(14.5, 2), Vector(14.5, 1) },

	};

	enum States {
		INIT,
		START,


		FADEIN1,
		FADEOUT1,


		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points, GameObject* object);
	States state;
	
	Texture* filter;
	Texture* bg;
	Texture* black;


	SoundEffect* ambience;
	Music* music;


	vector<dialogueInfo> dialogues;
	int timer;
	int dialogueN;
	int musicVol;



public:
	BadEnding2Scene();
	void reset() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;

};

