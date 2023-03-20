#pragma once
#include "../components/Text.h"
#include "../components/BoxText.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../structure/GameObject.h"
#include "../structure/Scene.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/checkML.h"

class Dialogue : public GameObject {
private:
	SDLUtils* sdl;
	int widthLetter;
	int heightLetter;


public:
	Dialogue(Scene* scene, Vector pos, int widthBox, float letterFrequency, Font* font, deque<string> texts) :
		GameObject(scene, _ecs::grp_HUD), sdl(SDLUtils::instance()), widthLetter(20), heightLetter(30) {

		Transform* transform = new Transform(this, Vector(pos.getX(), pos.getY()));
		new Image(this, &sdl->images().at("DIALOG_BOX"));
		new Text(this, texts, widthLetter, heightLetter, letterFrequency, font, widthBox);
		new BoxText(this, &sdl->images().at("KEYBOARD_KEYS_2"));
	}
};