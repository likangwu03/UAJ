#pragma once
#include "../../Structure/Scene.h"
#include "../../Utilities/Texture.h"
#include "../../GameObjects/ButtonGO.h"
class CoopHandler;
class CoopMenu : public Scene
{
private:

	static void bResume();
	static void bServer();
	static void bClient();

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

public:
	CoopMenu();
	~CoopMenu();

	void update() override;

	void init();

	//virtual void handleEvents();
	
};

