#include "KitchenIslandComp.h"

#include "../structure/Scene.h"
#include "../components/Ingredients.h"

#include "../utils/checkML.h"


using namespace std;
KitchenIslandComp::KitchenIslandComp(GameObject* parent) :
	Component(parent, id), sdl(SDLUtils::instance()), ingCloud(parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Ingredients>()) {

	w = parent->getComponent<Transform>()->getW() / 6;
	h = parent->getComponent<Transform>()->getH() / 2;
	x = parent->getComponent<Transform>()->getPos().getX();
	y = parent->getComponent<Transform>()->getPos().getY();
	font = new Font("assets/Fonts/8-bit Madness.ttf", 40);
	highlight = &sdl->images().at("ISLAND_HIGHLIGHT");
	selected = -1;
	hPos = { -w,-h };
	ingCloud->setKitchenIsland(this);

}

KitchenIslandComp::~KitchenIslandComp() {
	// se elimina la fuente cogida
	delete font;
	for (auto i : ing) delete i.second.f;
}

void KitchenIslandComp::render() {

	highlight->render(build_sdlrect(hPos.getX(), hPos.getY(), w, h));
	
	for (int i = 0; i < ing.size(); ++i) {
		ing[auxID[i]].t->render(build_sdlrect(x + w * (i % 6), y + w * (i / 6), w, h));
		ing[auxID[i]].b->render(build_sdlrect(x + w * (i % 6) + OFFSETX - (B_W - F_W) / 2, y + w * (i / 6) + OFFSETY - (B_H - F_H) / 2 + 1, B_W, B_H));
		ing[auxID[i]].f->render(build_sdlrect(x + w * (i % 6) + OFFSETX, y + w * (i / 6) + OFFSETY, F_W, F_H));
	}
	
}

void KitchenIslandComp::pickIngredient(int i) {
	if (i < ing.size() && ing[auxID[i]].n > 0) {
		//if(ingCloud->addIngredient(auxID[i]))
		--ing[auxID[i]].n;
		ingCloud->addIngredient(auxID[i]);
		delete ing[auxID[i]].f;
		ing[auxID[i]].f = new Texture(sdl->renderer(), to_string(ing[auxID[i]].n), *font, build_sdlcolor(0xFAF2E6ff));
	}
}

void KitchenIslandComp::selectedIng(int i) {
	if (i < ing.size() && selected != i) {
		selected = i;
		hPos = { x + w * (i % 6) , y + w * (i / 6) };
	}

}
void KitchenIslandComp::unselectIng(int i) {
	if (i < ing.size() && selected == i) {
		hPos = { -w,-h };
		selected = -1;
	}
}

void KitchenIslandComp::setIngredients(vector<pair<_ecs::_ingredients_id, int>> _ing) {
	auxID.clear();
	for (auto i : ing) {
		delete i.second.f;
	}
	ing.clear();

	//cargar info
	auxID = vector<_ecs::_ingredients_id>(_ing.size());

	for (int i = 0; i < _ing.size(); ++i) { // cleon: recorrido moderno? pues no. pues s?
		ing.insert({ _ing[i].first, {_ing[i].second, &sdl->images().at(to_string(_ing[i].first)),
		new Texture(sdl->renderer(), to_string(_ing[i].second), *font, build_sdlcolor(0xFAF2E6ff)), &sdl->images().at("KI_ICON")} });
		auxID[i] = _ing[i].first;
	}
}

void KitchenIslandComp::returnIngredient(_ecs::_ingredients_id id) {
	++ing[id].n;
	delete ing[id].f;
	ing[id].f = new Texture(sdl->renderer(), to_string(ing[id].n), *font, build_sdlcolor(0xFAF2E6ff));
}
