#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"

class ContinueMenu : public Scene
{
private:

	GameObject* bg;
	ButtonGO* buttonMainMenu;
	ButtonGO* buttonNewGame;
	ButtonGO* buttonContinue;
	Texture* image;
public:
	ContinueMenu();
	~ContinueMenu();
};

