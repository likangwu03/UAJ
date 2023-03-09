#pragma once
#include "../components/CartelTrigger.h"
#include "../components/ShoppingMenuComp.h"
#include "../structure//Scene.h"
class CartelManager 
{
private:
	CartelTrigger* selectedCartel;
	ShoppingMenuComp* menu;
	Scene* scene;
public:
	CartelManager(Scene* scene) :scene(scene),selectedCartel(nullptr),menu(scene->getConnectedScene()->getGameObject(hdr_SHOP_MENU1)->getComponent<ShoppingMenuComp>()) {}
	void signIn(CartelTrigger* c); //llamado por onTriggerEnter de cartelTrigger 
	void signOut(CartelTrigger* c); //llamado por onTriggerExit de cartelTrigger

	void openMenu();
	void closeMenu();
	_ecs::_ingredients_id getIngredient() { return selectedCartel->getIngredient(); }
	bool isSelected() { return (selectedCartel != nullptr);  }
};

