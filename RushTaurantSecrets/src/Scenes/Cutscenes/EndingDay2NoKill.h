#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;

class EndingDay2NoKill : public CinematicBaseScene {
private:
	const int TURNAROUNDTIME = 500;
	const vector<Vector> paths[1] = {
		{ Vector(19.5, 15) }
	};

	enum States {
		START,
		TURNTORIGHT,
		NONE
	};

	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;
	
	Texture* filter;
	Texture* bg;
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;
	int timer;

public:
	EndingDay2NoKill();
	void callAfterCreating() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

