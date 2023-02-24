#pragma once
#include "../components/CartelTrigger.h"
class CartelManager
{
public:
	CartelManager():selectedCartel(nullptr){}
	void signIn(CartelTrigger* c); //llamado por onTriggerEnter de cartelTrigger 
	void signOut(CartelTrigger* c); //llamado por onTriggerExit de cartelTrigger
private: 
	CartelTrigger* selectedCartel;
};

