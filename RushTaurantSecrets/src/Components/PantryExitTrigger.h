#pragma once
#include "../Structure/TriggerComp.h"
#include "../Utilities/SDLUtils.h"
#include "OtherPlayerComp.h"

class GameManager;
class Transform;
class Image;

class PantryExitTrigger : public TriggerComp {
private:
	const int MUSIC_VOL = 30;

	const Vector RESTAURANT_POS = { 640, 130 };
	GameObject* playerPantry, *otherPPantryObj;
	GameObject* playerRestaurant, *otherPRestObj;
	GameManager* gm;
	Transform* playerRestaurantTransform;
	Image* image;
	SoundEffect* doorSound;
	OtherPlayerComp* otherPPantryComp;

	SDLUtils* sdl;
	Music* pantryMusic;
	Music* restaurantMusic;
public:
	PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};
