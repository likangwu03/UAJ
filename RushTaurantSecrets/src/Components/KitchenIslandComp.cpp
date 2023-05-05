#include "KitchenIslandComp.h"

#include "../Structure/Scene.h"
#include "Ingredients.h"
#include "../Structure/Game.h"
#include "../Utilities/checkML.h"


using namespace std;
KitchenIslandComp::KitchenIslandComp(GameObject* parent) :
	Component(parent, id), sdl(SDLUtils::instance()), 
	ingCloud(parent->getScene()->getGameObject(_ecs::hdr_PLAYER)->getComponent<Ingredients>()),
	selectSound(&sdlutils().soundEffects().at("SELECT"))
{
	selectSound->setVolume(80);
	w = parent->getComponent<Transform>()->getW() / 6;
	h = parent->getComponent<Transform>()->getH() / 2;
	x = parent->getComponent<Transform>()->getPos().getX();
	y = parent->getComponent<Transform>()->getPos().getY();
	font = new Font(FONT_PATH, FONTSIZE);
	highlight = &sdl->images().at("ISLAND_HIGHLIGHT");
	selected = -1;
	hPos = { -w,-h };
	ingCloud->setKitchenIsland(this);

	KI_icon = &sdl->images().at("KI_ICON");
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
		ing[auxID[i]].b->render(build_sdlrect(x + w * (i % 6) + OFFSETX - (B_W - ing[auxID[i]].f->width()) / 2, y + w * (i / 6) + OFFSETY - (B_H - ing[auxID[i]].f->height()) / 2 + 1, B_W, B_H));
		ing[auxID[i]].f->render(build_sdlrect(x + w * (i % 6) + OFFSETX, y + w * (i / 6) + OFFSETY, ing[auxID[i]].f->width(), ing[auxID[i]].f->height()));
	}
	
}

void KitchenIslandComp::pickIngredient(int i, bool send) {
	if (send&&i < ing.size() && ing[auxID[i]].n > 0  && ingCloud->addIngredient(auxID[i]) ) {
		--ing[auxID[i]].n;
		delete ing[auxID[i]].f;
		ing[auxID[i]].f = new Texture(sdl->renderer(), to_string(ing[auxID[i]].n), *font, build_sdlcolor(0xFAF2E6ff));
		Message m;
		m.id = Message::msg_PICK_INGREDIENT;
		m.ingredinet.n = i;
		Game::get()->getCoopHandler()->send(m);
	}
	else if(!send)
	{
		--ing[auxID[i]].n;
		delete ing[auxID[i]].f;
		ing[auxID[i]].f = new Texture(sdl->renderer(), to_string(ing[auxID[i]].n), *font, build_sdlcolor(0xFAF2E6ff));
	}
}

void KitchenIslandComp::selectedIng(int i) {
	if (i < ing.size() && selected != i) {
		selected = i;
		hPos = { x + w * (i % 6) , y + w * (i / 6) };
		selectSound->play();
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
	for (auto i : ing) 
		delete i.second.f;
	
	ing.clear();

	//cargar info
	auxID = vector<_ecs::_ingredients_id>(_ing.size());

	int i = 0;
	for (auto ingredient : _ing) {
		auto texture = new Texture(sdl->renderer(), to_string(_ing[i].second), *font, build_sdlcolor(0xFAF2E6ff));
		ing.insert( { ingredient.first, {ingredient.second, &sdl->images().at(to_string(ingredient.first)), texture, KI_icon} });
		auxID[i] = ingredient.first;

		i++;
	}
}

void KitchenIslandComp::returnIngredient(_ecs::_ingredients_id id,bool send) {
	++ing[id].n;
	delete ing[id].f;
	ing[id].f = new Texture(sdl->renderer(), to_string(ing[id].n), *font, build_sdlcolor(0xFAF2E6ff));
	if (send) {
		Message m;
		m.id = Message::msg_RETURN_INGREDIENT;
		m.ingredinet.n = id;
		Game::get()->getCoopHandler()->send(m);
	}
}


void KitchenIslandComp::nextDay() {
	unselectIng(selected);
}


void KitchenIslandComp::receive(const Message& message) {
	if (message.id == Message::msg_PICK_INGREDIENT) 
		pickIngredient(message.ingredinet.n, false);
	
	else if (message.id == Message::msg_RETURN_INGREDIENT) 
		returnIngredient((_ecs::_ingredients_id)message.ingredinet.n, false);
	
}