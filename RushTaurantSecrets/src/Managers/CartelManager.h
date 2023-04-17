#pragma once
#include "../Components/CartelTrigger.h"
#include "../Components/ShoppingMenuComp.h"

#include "../Structure/GameManager.h"
#include "../Scenes/GameScenes/SuperMarket.h"

class CartelManager {

private:
	CartelTrigger* selectedCartel;
	ShoppingMenuComp* menu;
	Scene* scene;
	SoundEffect* selectSound;
public:
	CartelManager(Scene* scene);
	void signIn(CartelTrigger* c); //llamado por onTriggerEnter de cartelTrigger 
	void signOut(CartelTrigger* c); //llamado por onTriggerExit de cartelTrigger

	void openMenu();
	void closeMenu();
	_ecs::_ingredients_id getIngredient() { return selectedCartel->getIngredient(); }
	bool isSelected() { return (selectedCartel != nullptr);  }
};

