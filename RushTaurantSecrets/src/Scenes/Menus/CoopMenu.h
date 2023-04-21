#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"
class CoopHandler;
class CoopMenu : public Scene
{
private:
	GameObject* bg;
	ButtonGO* buttonResume;
	ButtonGO* buttonServer;
	ButtonGO* buttonClient;

	CoopHandler* coop;
	Texture* image;
	Texture* waiting;
	string ip="localhost";
	bool server;
	bool wait;
	Font* text;

	const int NUM_BUTTON = 3;
	int button;
public:
	CoopMenu();
	~CoopMenu();

	void update() ;
	void handleEvents() override;
	void init();
	void selectedButton(int selected);

	
};

