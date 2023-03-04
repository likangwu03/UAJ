#pragma once
#include "../components/CartelTrigger.h"

class CartelManager : public Singleton<CartelManager>
{
	friend Singleton<CartelManager>;
private:
	CartelTrigger* selectedCartel;
	CartelManager() :selectedCartel(nullptr) {}
public:
	void signIn(CartelTrigger* c); //llamado por onTriggerEnter de cartelTrigger 
	void signOut(CartelTrigger* c); //llamado por onTriggerExit de cartelTrigger

	_ecs::_ingredients_id getIngredient() { return selectedCartel->getIngredient(); }
	bool isSelected() { 
		return (selectedCartel != nullptr);  
	}
};

