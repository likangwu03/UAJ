#pragma once
#include "../Structure/TriggerComp.h"

class GameManager;
class Transform;
class Image;

class PantryExitTrigger : public TriggerComp {
private:
	GameObject* playerPantry;
	GameObject* playerRestaurant;
	GameManager* gm;
	Transform* playerRestaurantTransform;
	Image* image;

public:
	PantryExitTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};
