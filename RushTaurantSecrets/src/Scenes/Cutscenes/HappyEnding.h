#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class CinematicNPC;

class HappyEnding : public CinematicBaseScene {
private:
	const int DELAY = 1000;
	const Vector BOXPOS = Vector(150, 20);
	const float BOXW = 700, LETTERFREQ = 0.01f * 1000;
	const Animator::AnimParams AP = { 18,18,1 };

	const int DOORFRAMES = 5, DOORFREQ = 1;
	const float DOORW = 48, DOORH = 144;
	const SDL_Rect DOORPOS = build_sdlrect(554, 240, DOORW * 2, DOORH * 2);
	
	const float RESTSIZE = 0.6666666667;

	//struct 

	const vector<Vector> paths[6] = {
		{ Vector(8.8, 2), Vector(14.5, 2), Vector(14.5, 1) },
		{ Vector(14.5, 1), Vector(14.5, 5), Vector(22, 5) },
		{ Vector(22, 5), Vector(22, 10),  Vector(17.8, 10), },
		{ Vector(17.8, 10), Vector(17.8, 16), Vector(10, 16) },
		{ Vector(10,16), Vector(10,20) },
		{ Vector(29,4.5), Vector(28,4.5), Vector(31,4.5) },

	};

	enum States {
		START,
		WAKE,
		SIT,
		STAND,
		WINDOW,
		D2,
		CLOSET,
		FADEIN1,
		FADEOUT1,
		D3,
		D4,
		WALKDOOR,
		OPENDOOR,
		D5,
		WALKOUT,
		D6,
		D7,
		FADEIN2,
		FADEOUT2,
		RESTAURANT,


		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points);
	States state;
	
	Texture* filter;
	Texture* bg;
	Texture* black;
	Texture* door;
	Texture* top;

	SoundEffect* nightAmbience;
	Music* nightMusic;

	vector<dialogueInfo> dialogues;
	int timer;
	int dialogueN;
	int doorFrame;

	vector<

public:
	HappyEnding();
	void reset() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

