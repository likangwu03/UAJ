#include "Ingredients.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"

using namespace _ecs;

Ingredients::Ingredients(GameObject* parent) :Component(parent, id), sdl(SDLUtils::instance()), texture(nullptr) {
	transform = parent->getComponent<Transform>();
}

void Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	for (int i = 0; i < ingredients->size();++i) {
		ingredients->push_back(ingr);
	}
	
}

void Ingredients::removeLastIngredient(_ingredients_id ing) {
	ingredients->pop_back();
}

void Ingredients::removeAllIngredients() {
	
}

void Ingredients::removeWhenExit() {

}

void Ingredients::render() {
	SDL_Rect dest;
	dest.x = transform->getPos().getX();
	dest.y = transform->getPos().getY();
	dest.w = transform->getW();
	dest.h = transform->getH();
	
	for (auto it = ingredients.begin(); it != ingredients.end(); ++it) {
		texture = &((*sdl).images().at(to_string(*it)));
		texture->render(dest);
	}
}
