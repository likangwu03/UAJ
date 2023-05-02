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

	struct NPCInfo {
		CinematicNPC* npc;
		Vector pos;
		movementState state;
		GOOrientation orientation;
	};

	const vector<Vector> paths[6] = {
		{ Vector(8.8, 2), Vector(14.5, 2), Vector(14.5, 1) },
		{ Vector(14.5, 1), Vector(14.5, 5), Vector(22, 5) },
		{ Vector(22, 5), Vector(22, 10),  Vector(17.8, 10), },
		{ Vector(17.8, 10), Vector(17.8, 16), Vector(10, 16) },
		{ Vector(10,16), Vector(10,20) },
		{ Vector(27,4.5), Vector(31,4.5), Vector(31,7.5), Vector(31,4.5), Vector(27,4.5) },

	};
	const vector<Vector> waiterPaths[2] = {
		{ Vector(27, 11), Vector(30,11), Vector(30,9), Vector(30,12), Vector(24,12), Vector(24,13.5) },
		{ Vector(20, 7), Vector(20,12), Vector(12,12), Vector(12,10) },

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
		FADEIN3,
		FADEOUT3,
		PANTRY,
		FADEIN4,
		FADEOUT4,
		CELEBRATE,
		D8,
		D9,
		D10,
		D11,
		D12,
		OUT,
		NONE
	};

	void addPath(const vector<Vector>& points, GameObject* object);
	States state;
	
	Texture* filter;
	Texture* bg;
	Texture* black;
	Texture* door;
	Texture* top;

	SoundEffect* ambience;
	Music* music;
	SoundEffect* cheer;

	vector<dialogueInfo> dialogues;
	int timer;
	int dialogueN;
	int doorFrame;
	int musicVol;

	vector<NPCInfo> npcs;
	CinematicNPC* waiter1;
	CinematicNPC* waiter2;
	CinematicNPC* guard1;
	CinematicNPC* guard2;

public:
	HappyEnding();
	void reset() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;

private:
	void addClient(string txt, Vector pos, GOOrientation orientation);
};

