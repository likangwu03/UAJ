#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class ContinueMenu : public Scene
{
private:
	static void bMainMenu();
	static void bNewGame();
	static void bContinue();

	GameObject* bg;
	ButtonGO* buttonResume;
	ButtonGO* buttonNewGame;
	ButtonGO* buttonContinue;
	Texture* image;
public:
	ContinueMenu();
	~ContinueMenu();
};

