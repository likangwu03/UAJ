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

	ButtonGO* buttonResume2;
	ButtonGO* buttonConfir;

	GameObject* IP;
	CoopHandler* coop;

	Texture* image;
	Texture* waiting;
	Texture* waiting2;
	Texture* textBox;

	string ip_="localhost";

	const float WIDTH = SDLUtils::instance()->width();
	const float HEIGHT = SDLUtils::instance()->height();

	bool server;
	bool wait;
	bool enterIp_;

	Font* text_ip;

	const int NUM_BUTTON = 3;
	int button;
public:
	CoopMenu();
	~CoopMenu();

	void update() ;
	void handleEvents() override;
	
	void selectedButton(int selected);

	void render()override;

	void onWaiting();

	void enterIp();

	void goBack();

};

