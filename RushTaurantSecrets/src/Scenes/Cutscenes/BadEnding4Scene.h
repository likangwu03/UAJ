#pragma once
#include "../../Scenes/Cutscenes/CinematicBaseScene.h"
#include "../../GameObjects/Player.h"
#include "../../Components/StraightMovement.h"
#include <vector>

using namespace std;
//struct dialogueInfo {
//
//};

class BadEnding4Scene: public CinematicBaseScene
{
private:
	GameObject* player;
	StraightMovement* straightMovement;
	//vector<dialogueInfo> dialogues;
public:
	BadEnding4Scene();
	void renderCinematic() override;
	void finishScene()override;
	void update()override;
};