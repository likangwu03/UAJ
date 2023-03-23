#pragma once
#include "../Structure/Scene.h"
#include "../Utilities/Texture.h"
#include "../GameObjects/ButtonGO.h"

class OptionsMenu : public Scene
{
private:
	static void mMenu();
	static void bResume();

	GameObject* bg;
	ButtonGO* buttonResume;
	Texture* image;
public:
	OptionsMenu();
	~OptionsMenu();

	void handleEvents();

};

