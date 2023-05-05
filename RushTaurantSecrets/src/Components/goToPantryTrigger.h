#pragma once
#include "../Structure/TriggerComp.h"
#include "../Utilities/SDLUtils.h"
#include "OtherPlayerComp.h"

class GameManager;
class Image;

static const int MUSIC_VOL = 30;

class GoToPantryTrigger : public TriggerComp {
private:
	const Vector PANTRY_POS = { 800, 580 };
	
	

	GameManager* gm;
	GameObject* playerRestaurant, *otherPRestObj;
	GameObject* playerPantry, *otherPPantryObj;
	Transform* playerPantryTransform;
	Image* image;
	SoundEffect* doorSound;
	OtherPlayerComp* otherPRestComp;

	SDLUtils* sdl;
	Music* pantryMusic;
	Music* restaurantMusic;
public:
	GoToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};