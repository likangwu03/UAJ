#pragma once
#include "CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

struct dialogueInfo;
class TransitionScene;
class EndingDay1Scene : public CinematicBaseScene
{
	const vector<Vector> paths[1] = {
		{ Vector(12, 5) }
	};

	enum States {
		START,
		D1,
		OUT,
		NONE
	};

	Texture* bg;
	Texture* filter;
	Texture* top;
	Transform* transform;
	void addPath(const vector<Vector>& points);
	States state;
private:
	GameObject* player;
	StraightMovement* straightMovement;

	vector<dialogueInfo> dialogues;
	vector<Vector> playerPoints;

public:
	EndingDay1Scene();
	void reset() override;
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};

