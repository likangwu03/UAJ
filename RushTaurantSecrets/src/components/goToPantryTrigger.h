#pragma once
#include "TriggerComp.h"

class SceneManager;
class goToPantryTrigger : public TriggerComp {
private:
	SceneManager* sceneM;

	//Restaurant* restaurant; --> debe obtenerlo en el constructor a través del objeto que contiene el trigger
public:
	goToPantryTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	virtual void onTriggerEnter();
};