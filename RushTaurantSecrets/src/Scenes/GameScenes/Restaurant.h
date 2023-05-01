#pragma once
#include "../../Structure/Scene.h"
#include "../HUD/UIRestaurant.h"
#include "Pantry.h"

class DishCombinator;
class CollisionsManager;
class TextBox;
class DayManager;
//class TimeOfDay;

class Restaurant : public Scene {
private:
	const int MUSIC_VOL = 30;

	const float RESIZEFACTOR = 0.6666666667;
	const Vector INITIAL_POS = { 750, 240 }, PANTRY_POS = { 750, 240 };

	Pantry* pantry;
	//TimeOfDay* timeOfDay;
	UIRestaurant* ui;

	DishCombinator* dc;
	CollisionsManager* cm;
	DayManager* dm;
	
	GameObject* player;

	vector<_ecs::_dish_id> menu() const;
	//vector<_ecs::_dish_id> dailyMenu;

	SDLUtils* sdl;
	Music* restaurantMusic;
	Music* pantryMusic;
public:
	Restaurant();
	~Restaurant();

	void reset();

	void callAfterCreating();

	UIRestaurant* getUI() { return ui; }
	
	void render();
	void update();
	void _update();
	void handleEvents();
	void refresh();
	virtual void initComponent();
	void receive(const Message& m);
	void _receive(const Message& m);

	float getResizeFactor() { return RESIZEFACTOR; }
	void createMap();


};