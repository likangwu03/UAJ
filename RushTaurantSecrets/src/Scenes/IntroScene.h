#pragma once
#include "../Scenes/CinematicBaseScene.h"
#include "../GameObjects/Player.h"
#include "../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class IntroScene : public CinematicBaseScene
{
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
		NONE
	};
	Texture* bg;
	Texture* filter;
	Texture* top;
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
	void callAfterCreating() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

