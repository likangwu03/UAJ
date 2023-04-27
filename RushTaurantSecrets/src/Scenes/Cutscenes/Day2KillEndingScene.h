#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
struct dialogueInfo;
class Day2KillEndingScene : public CinematicBaseScene
{
	enum States {
		START,
		D1,
		PHONE,
		PATHING,
		D2,
		OUT,
		NONE
	};
	Texture* bg;
	Texture* black;
	Transform* transform;
	SoundEffect* phonecall;
	void addPath(const vector<Vector>& points);
	States state;

	const int START_TIME = 3;

private:
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;
	vector<Vector> enterPoints;
	vector<Vector> phonePoints;

public:
	Day2KillEndingScene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

