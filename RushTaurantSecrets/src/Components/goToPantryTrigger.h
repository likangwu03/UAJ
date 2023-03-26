#pragma once
#include "../Structure/TriggerComp.h"

class GameManager;
class Image;

class GoToPantryTrigger : public TriggerComp {
private:
	GameManager* gm;
	GameObject* playerRestaurant;
	GameObject* playerPantry;
	Transform* playerPantryTransform;
	Image* image;

public:
	GoToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void isOverlapping();
	virtual void onTriggerExit();
};