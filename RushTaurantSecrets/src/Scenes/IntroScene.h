#pragma once
#include "../Scenes/CinematicBaseScene.h"
#include "../GameObjects/Player.h"
class IntroScene : public CinematicBaseScene
{
	enum States {
		START, 
		ENTERING,//sonido puerta
		ARRIVE,//1
		D1,
		D2,
		D3,
		D4,
		D5,
		D6,
		OUT       
	};
private:
	Texture* bg;
	Texture* filter;
	GameObject* player;
	const float WIDTH, HEIGHT;
	States state;
public:
	IntroScene();
	//void handleEvents()override;
	void callAfterCreating() override;
	void update()override;
	void renderCinematic () override;
	void finishScene()override;
};

