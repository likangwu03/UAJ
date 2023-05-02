#pragma once
#include "CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../GameObjects/CinematicNPC.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class TransitionScene;
class BadEnding1Scene : public CinematicBaseScene
{
private:
	const float RESIZEFACTOR = 0.6666666667;

	// 26 DIALOGOS XDDD
	enum States {
		START,
		ARRIVE,//1
		D1,
		D2,
		RESTAURANT_FADEOUT,
		BEDROOM_FADEIN,
		PHONECALL,
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
		BEDROOM_FADEOUT,
		RESTAURANT_FADEIN,
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
		OUT,
		NONE
	};

	Texture* bg;
	Texture* filter;
	Texture* top;
	SoundEffect* phonecall;

	Music* dramaticMusic;
	void addPath(const vector<Vector>& points);
	States state;
	const float START_TIME = 3;

	GameObject* client1;
	GameObject* client2;
	StraightMovement* straightMovementc1;
	StraightMovement* straightMovementc2;

	vector<dialogueInfo> dialogues;

	vector<Vector> playerPoints;
	vector<Vector> playerPoints2;
	vector<Vector> client1Points;
	vector<Vector> client2Points;

public:
	BadEnding1Scene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;

};

