#pragma once
#include "../Structure/TriggerComp.h"
#include "../Utilities/SDLUtils.h"

class GameManager;
class Image;

class GoToPantryTrigger : public TriggerComp {
private:
	const Vector PANTRY_POS = { 800, 580 };

	GameManager* gm;
	GameObject* playerRestaurant;
	GameObject* playerPantry;
	Transform* playerPantryTransform;
	Image* image;
	SoundEffect* doorSound;
public:
	GoToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};