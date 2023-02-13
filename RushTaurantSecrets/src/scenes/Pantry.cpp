#include "Pantry.h"
#include "Restaurant.h"

void Pantry::linkRestaurant(Restaurant* rest) {
	this->rest = rest;
	//ui = rest->getUI();
}

void Pantry::render() {
	Scene::render();
	//ui->render();
}

void Pantry::update() {
	Scene::update();
	rest->Scene::update();
}

void Pantry::handleEvents() {
	Scene::handleEvents();
	//ui->handleEvents();
}