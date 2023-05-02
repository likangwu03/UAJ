#pragma once
#include "../../Structure/Scene.h"
#include "../../Managers/CollisionsManager.h"
#include "../../GameObjects/Clock.h"
#include "../../Scenes/HUD/UIPantry.h"

class Restaurant;

class Pantry : public Scene {
private:
	const int MUSIC_VOL = 30;

	const float RESIZEFACTOR = 0.8333333333;
	GameObject* player;
	CollisionsManager* collisionsManager;
	Restaurant* rest;
	UIPantry* pantryUI;

	SDLUtils* sdl;
	Music* restaurantMusic;
	Music* pantryMusic;

public:
	Pantry(UIPantry* pUI);
	~Pantry();

	void render();
	void update();
	void _update();
	void handleEvents();
	void reset();
	void refresh();
	void receive(const Message& m);
	
	Restaurant* getRestaurant() { return rest; }
	void init();

	float getResizeFactor() { return RESIZEFACTOR; }
	void createMap();

	void callAfterCreating();
	void resumeMusic()override;
	void resumeSound()override;
	void haltSound()override;

	void initCoopMode(bool server) override;
	void quitCoopMode() override;
};