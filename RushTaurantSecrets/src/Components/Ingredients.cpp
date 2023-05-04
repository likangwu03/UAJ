#include "../Utilities/checkML.h"
#include "Ingredients.h"


Ingredients::Ingredients(GameObject* parent) : Component(parent, id), sdl(SDLUtils::instance()), coord(),
returnIng(&sdlutils().soundEffects().at("RETURN_ING")),
pickIng(&sdlutils().soundEffects().at("PICK_ING")), return_icon(&sdlutils().images().at("RETURN_ICON")), clean_icon(&sdlutils().images().at("CLEAN_ICON"))
{												  
	bubble_tex = &((*sdl).images().at("BUBBLE")); 
	dest_bubble = { BUBBLE_X, BUBBLE_Y, BUBBLE_W, BUBBLE_H };
	dest.w = dest.h = ING_SIZE;
}
void Ingredients::initComponent() {
	showControl = new ShowControlComp(parent, { {ControlsType::key_R,ControlsType::play_Cross,ControlsType::xbox_A,Vector(15,20),30,30} ,{ControlsType::key_X,ControlsType::play_Triangle,ControlsType::xbox_Y,Vector(15,50),30,30}});

}
bool Ingredients::addIngredient(_ecs::_ingredients_id ingr) {
	// si el iterador llega al final, es que el iterador no est�
	if (ingredients.size() < MAX_INGREDIENTS && std::find(ingredients.begin(), ingredients.end(), ingr) == ingredients.end()) {

		ingredients.push_back(ingr);

		if (ingredients.size() == 1)
			coord.push_back(STARTING_COORDS);
		else {
			for (auto& coords : coord) {
				coords.first -= ING_OFFSET / 2;
			}
			//Nuevas coordenadas del nuevo ingrediente
			coord.push_back({ coord.back().first, ING_Y});
			coord.back().first += ING_OFFSET;
		}
		pickIng->play();
		return true;
	}
	else return false;
}

void Ingredients::removeLastIngredient() {
	if (!ingredients.empty()) {
 		kitchenIsland->returnIngredient(ingredients.back());
		ingredients.pop_back();

		for (auto& coords : coord)
			coords.first += ING_OFFSET / 2;
		
		returnIng->play();
		coord.pop_back();
	}
}

void Ingredients::removeAllIngredients() {
	while (!ingredients.empty()) {
		//devolver a la mesa
		removeLastIngredient();
	}
}

void Ingredients::cookingIngredients() {
	int i = ingredients.size(); 
	while (i != 0) {
		ingredients.pop_back();

		for (auto& coords : coord)
			coords.first += (0.5 * ING_OFFSET);

		coord.pop_back();
		--i;
	}
}

void Ingredients::render() {
	if (!ingredients.empty()) {
		bubble_tex->renderFrame(dest_bubble, 0, ingredients.size() - 1, 0);
		showControl->render(Vector(dest_bubble.x+ dest_bubble.w-(MAX_INGREDIENTS- ingredients.size()*20)-96, dest_bubble.y));
		return_icon->render(build_sdlrect(dest_bubble.x + dest_bubble.w - 60 - (MAX_INGREDIENTS - ingredients.size() * 20), dest_bubble.y+5,30,30));
		clean_icon->render(build_sdlrect(dest_bubble.x + dest_bubble.w - 60- (MAX_INGREDIENTS - ingredients.size() * 20), dest_bubble.y + 35, 30, 30));
		
		int k = 0; // mejor con un iterador.
		for (auto ingredient : ingredients) {
			Texture* texture = &((*sdl).images().at(to_string(ingredient)));
			dest.x = coord[k].first;
			dest.y = ING_Y;
			texture->render(dest);
			++k;
		}
	}
	
}

void Ingredients::nextDay() {
	ingredients.clear();
}
