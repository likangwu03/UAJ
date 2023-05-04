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


	const vector<Vector> paths[7] = {
		{ Vector(26,7.6), Vector(20,7.6), Vector(20,11), Vector(28,11), Vector(28,14), Vector(41,14) },
		{ Vector(35, 14), Vector(25, 14) },
		{ Vector(25, 14), Vector(18.5, 14), Vector(18.5, 6) },
		{ Vector(18.5, 6), Vector(18.5, 14), Vector(25, 14) },
		{ Vector(19.5, 4), Vector(19.5, 16) },
		{ Vector(19.5, 16), Vector(19.5, 24) },
		{ Vector(41, 15), Vector(36, 15) }
	};

	enum States {
		INIT,
		START,
		D2,
		D3,
		D4,
		D5,
		D6,
		D7,
		D8,
		WALKOUT,
		FADEIN1,
		FADEOUT1,
		WALKIN,
		D9,
		D10,
		D11,
		D12,
		FADEIN2,
		RING,
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
		FADEOUT2,
		D25,
		D26,
		D27,
		FADEIN3,
		FADEOUT3,
		D28,
		FADEIN4,
		D29,

		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points);
	States state;
	
	Texture* filter;
	Texture* bg;
	Texture* black;
	Texture* top;


	SoundEffect* ambience;
	Music* music;
	SoundEffect* phonecall;


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

