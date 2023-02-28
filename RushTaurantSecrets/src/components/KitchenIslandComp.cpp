#include "KitchenIslandComp.h"
#include "../utils/checkML.h"
#include "../structure/Scene.h"

using namespace std;
KitchenIslandComp::KitchenIslandComp(GameObject* parent, vector<pair<_ecs::_ingredients_id, int>> _ing) :
	Component(parent, id), sdl(SDLUtils::instance()), ingCloud(parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Ingredients>()) {
	w = parent->getComponent<Transform>()->getW() / 6;
	h = parent->getComponent<Transform>()->getH() / 2;
	x = parent->getComponent<Transform>()->getPos().getX();
	y = parent->getComponent<Transform>()->getPos().getY();
	f = new Font("assets/Fonts/8-bit Madness.ttf", 40);
	highlight = &sdl->images().at("ISLAND_HIGHLIGHT");
	selected = -1;
	//cargar info
	for (auto i : _ing) {
		ing.push_back({ i.first, i.second, &sdl->images().at(to_string(i.first)), 
			new Texture(sdl->renderer(), to_string(i.second), *f, build_sdlcolor(0xFAF2E6ff)), &sdl->images().at("KI_ICON") } );
	}

	/*for (int i = 0; i < _ing.size(); ++i) // cleon: recorrido moderno? pues no. pues sí. -> Arreglado
		ing.push_back({ _ing[i].first,_ing[i].second,&sdl->images().at(to_string(_ing[i].first)),
		new Texture(sdl->renderer(), to_string(_ing[i].second), *f, build_sdlcolor(0xFAF2E6ff)),
			&sdl->images().at("KI_ICON") });
	*/

}

KitchenIslandComp::~KitchenIslandComp() {
	// se elimina la fuente cogida
	delete f;
	for (auto i : ing) delete i.f;
	//for (int i = 0; i < ing.size(); ++i) delete ing[i].f; // cleon: recorrido moderno? pues también. -> Arreglado
	
}

void KitchenIslandComp::render() {

	highlight->render(build_sdlrect(hPos.getX(), hPos.getY(), w, h));
	for (int i = 0; i < ing.size(); ++i) {
		ing[i].t->render(build_sdlrect(x + w * (i % 6), y + w * (i / 6), w, h));
		ing[i].b->render(build_sdlrect(x + w * (i % 6) + OFFSETX - (B_W - F_W) / 2, y + w * (i / 6) + OFFSETY - (B_H - F_H) / 2 + 1, B_W, B_H));
		ing[i].f->render(build_sdlrect(x + w * (i % 6) + OFFSETX, y + w * (i / 6) + OFFSETY, F_W, F_H));
	}
}

void KitchenIslandComp::pickIngredient(int i) {
	if (i < ing.size() && ing[i].n > 0) {
		--ing[i].n;
		ingCloud->addIngredient(ing[i].id);
		delete ing[i].f;
		ing[i].f = new Texture(sdl->renderer(), to_string(ing[i].n), *f, build_sdlcolor(0xFAF2E6ff));
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