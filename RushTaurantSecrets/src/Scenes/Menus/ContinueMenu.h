#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class ContinueMenu : public Scene
{
private:
	const int NUM_BUTTON = 2;
	int button;

	GameObject* bg;
	ButtonGO* buttonMainMenu;
	ButtonGO* buttonNewGame;
	ButtonGO* buttonContinue;
	Texture* image;
public:
	ContinueMenu();
	~ContinueMenu();
	void handleEvents();
	void selectedButton(int selected);
};

