#pragma once
#include "../Structure/Scene.h"
#include "../Utilities/Texture.h"
#include "../GameObjects/ButtonGO.h"

class GameOverScene : public Scene
{
private:
	static void mMenu();
	GameObject* bg;
	ButtonGO* buttonMainMenu;
	Texture* image;
public:
	GameOverScene();
	~GameOverScene();

	void setGameOver(endingType type);


};

