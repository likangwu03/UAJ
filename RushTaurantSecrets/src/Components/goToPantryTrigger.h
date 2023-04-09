#pragma once
#include "../Structure/TriggerComp.h"
#include "../Utilities/SDLUtils.h"

class GameManager;
class Image;

class GoToPantryTrigger : public TriggerComp {
private:
	const Vector PANTRY_POS = { 800, 580 };
	// hacer global
	const int MUSIC_VOL = 30;

	GameManager* gm;
	GameObject* playerRestaurant;
	GameObject* playerPantry;
	Transform* playerPantryTransform;
	Image* image;
	SoundEffect* doorSound;

	SDLUtils* sdl;
	Music* pantryMusic;
	Music* restaurantMusic;
public:
	GoToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};