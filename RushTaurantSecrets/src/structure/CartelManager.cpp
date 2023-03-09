#include "CartelManager.h"
void CartelManager::signIn(CartelTrigger* c) {
	if (c == selectedCartel)return;
	if (selectedCartel != nullptr) //si ya existi¨¢ un cartel seleccionado
		selectedCartel->unHighlight(); //se deselecciona
	selectedCartel = c; //nuevo seleccionado
	selectedCartel->highlight();

}
void CartelManager::signOut(CartelTrigger* c) {
	if (c == selectedCartel) {
		c->unHighlight();
		selectedCartel = nullptr;
	}

}

void CartelManager::openMenu() {
	if (selectedCartel != nullptr)
		menu->openMenu(selectedCartel->getIngredient());
}
void CartelManager::closeMenu() {
	if (selectedCartel == nullptr)
		menu->closeMenu();
}