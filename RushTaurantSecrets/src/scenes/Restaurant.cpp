#include "Restaurant.h"
#include "Pantry.h"

void Restaurant::linkPantry(Pantry* pantry) {
	this->pantry = pantry;
}

void Restaurant::render() {
	Scene::render();
	ui->render();
}

void Restaurant::update() {
	Scene::update();
	pantry->Scene::update();
}

void Restaurant::handleEvents() {
	Scene::handleEvents();
	ui->handleEvents();
}