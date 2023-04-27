#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class IntroScene : public CinematicBaseScene
{
	const vector<Vector> introPath[2] = {
		{Vector(40, 14), Vector(28, 14)},
		{Vector(18, 14),Vector(18,10)}
	};

	enum States {
		START, 
		ENTERING,//sonido puerta
		ARRIVE,//1
		D1,
		D2,
		D3, 
		D31,
		D4,
		D5,
		D51,
		D6,
		OUT,
		D71,
		D72,
		WAITD7,
		NONE
	};
	Texture* bg;
	Texture* filter;
	Texture* top;
	Texture* black;
	SoundEffect* nightAmbience;
	Music* nightMusic;
	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;
	
private:
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;

public:
	IntroScene();
	void reset() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

