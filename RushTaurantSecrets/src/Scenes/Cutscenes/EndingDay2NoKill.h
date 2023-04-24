#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>
using namespace std;
struct dialogueInfo;
class EndingDay2NoKill : public CinematicBaseScene
{
	enum States {
		START,
		NONE
	};

	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;
	
private:
	Texture* filter;
	Texture* bg;
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;

public:
	EndingDay2NoKill();
	void callAfterCreating() override;
	void renderCinematic () override;
	void finishScene()override;
	void update()override;
};

