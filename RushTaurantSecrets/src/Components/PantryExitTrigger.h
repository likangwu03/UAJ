#pragma once
#include "../Structure/TriggerComp.h"
#include "../Utilities/SDLUtils.h"

class GameManager;
class Transform;
class Image;

class PantryExitTrigger : public TriggerComp {
private:
	const Vector RESTAURANT_POS = { 640, 130 };
	GameObject* playerPantry;
	GameObject* playerRestaurant;
	GameManager* gm;
	Transform* playerRestaurantTransform;
	Image* image;
	SoundEffect* doorSound;
public:
	PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};
