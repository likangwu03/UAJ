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
	f = new Font("assets/Fonts/Arcadepix Plus.ttf", 25);
	//cargar info
	for (int i = 0; i < _ing.size(); ++i) 

		ing.push_back({ _ing[i].first,_ing[i].second,&sdl->images().at(to_string(_ing[i].first)), 
			new Texture(sdl->renderer(), to_string(_ing[i].second), *f, build_sdlcolor(0xFAF2E6ff)),
			new Texture(sdl->renderer(), to_string(_ing[i].second), *f, build_sdlcolor(0x622609ff)) });

}
void KitchenIslandComp::render() {

	for (int i = 0; i < ing.size(); ++i) { 
		ing[i].t->render(build_sdlrect(x + w * (i % 6), y + w * (i / 6), w, h));
		ing[i].b->render(build_sdlrect(x + w * (i % 6) + OFFSETX -(B_W-F_W)/2 ,y + w * (i / 6) + OFFSETY -(B_H- F_H) / 2, B_W+B_W*(ing[i].n/10)*0.5, B_H));
		ing[i].f->render(build_sdlrect(x + w * (i % 6) + OFFSETX, y + w * (i / 6)+ OFFSETY,  F_W + F_W * (ing[i].n / 10) * 0.5, F_H));
	}

}

void KitchenIslandComp::pickIngredient(int i) {
	if (ing[i].n > 0) { 
		--ing[i].n;
		ingCloud->addIngredient(ing[i].id);
		delete ing[i].f;
		delete ing[i].b;
		ing[i].f = new Texture(sdl->renderer(), to_string(ing[i].n), *f, build_sdlcolor(0xFAF2E6ff));
		ing[i].b = new Texture(sdl->renderer(), to_string(ing[i].n), *f, build_sdlcolor(0x622609ff));
	}
}
