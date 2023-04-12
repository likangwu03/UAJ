#pragma once
#include "../Scenes/CinematicBaseScene.h"
#include "../GameObjects/Player.h"
class IntroScene : public CinematicBaseScene
{
private:
	Texture* bg;
	Texture* filter;
	GameObject* player;
	const float WIDTH, HEIGHT;
public:
	IntroScene();
	//void handleEvents()override;
	void callAfterCreating() override;
	
	void renderCinematic () override;
	void finishScene()override;
};

