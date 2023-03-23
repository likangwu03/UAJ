#include "ClientStateRender.h"
#include "../Structure/GameObject.h"
#include "ClientState.h"

#include "../Utilities/checkML.h"

ClientStateRender::ClientStateRender(GameObject* _parent) :Component(_parent, id),
transform(parent->getComponent<Transform>()), anim(parent->getComponent<UIAnimator>()),
state(nullptr), sdl(SDLUtils::instance())
{
	textures.bubble = &((*sdl).images().at("BUBBLE_ICON"));
	textures.takingNote = &((*sdl).images().at("CLIENT_TAKINGNOTE_ICON_ANIM"));
	textures.thinking = &((*sdl).images().at("CLIENT_THINKING_ICON_ANIM"));
	textures.eating = &((*sdl).images().at("CLIENT_EATING_ICON_ANIM"));

	anim->setActive(false); //al principio no tiene ning¨²n UIAnim
};


void ClientStateRender::clientStateIsReady() {
	state = parent->getComponent<ClientState>();
}

void ClientStateRender::renderThinkingState() {
	if(!anim->isActive())
		anim->setActive(true);
	anim->setTexture(textures.thinking, 0, 7, 0);
}

void ClientStateRender::renderTakingNoteState() {
	if (!anim->isActive())
		anim->setActive(true);
	anim->setTexture(textures.takingNote, 0, 0, 0);
}

void ClientStateRender::renderOrderingState() {
	if (!anim->isActive())
		anim->setActive(true); 
	textures.dish = &((*sdl).images().at(to_string(state->getOrderedDish())));
}

void ClientStateRender::renderEatingState() {
	if (!anim->isActive())
		anim->setActive(true);
	anim->setTexture(textures.eating, 0, 2, 0, 20);
}

void ClientStateRender::renderFinishEatState() {
	if (anim->isActive())
		anim->setActive(false);
}
void ClientStateRender::render() {

	switch (state->getState())
	{
	case ClientState::ORDERED: //esperando el plato
		SDL_Rect dest;
		dest.x = transform->getPos().getX() + BUBBLE_OFFSETX;
		dest.y = transform->getPos().getY() + BUBBLE_OFFSETY;
		dest.w = BUBBLE_WIDTH;
		dest.h = BUBBLE_HEIGHT;
		textures.bubble->render(dest);
		//dish
		if (textures.dish != nullptr) {
			dest.x = (dest.x + BUBBLE_WIDTH / 2) - DISH_WIDTH / 2 + DISH_OFFSETX;
			dest.y = dest.y + BUBBLE_HEIGHT / 2 - DISH_HEIGHT / 2 + DISH_OFFSETY;
			dest.w = DISH_WIDTH;
			dest.h = DISH_HEIGHT;
			textures.dish->render(dest);
		}

		break;
	}
}