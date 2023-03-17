#pragma once
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
	Font* font;

public:
	Dialogue(Scene* scene, Vector pos, int widthBox, float letterFrequency, deque<string> texts):
		GameObject(scene, _ecs::grp_HUD), sdl(SDLUtils::instance()) {

		font = new Font("assets/Fonts/8-bit Madness.ttf", 50);
		int width = widthBox + 100, height;
		int widthLetter = 20, heightLetter = 30;

		Transform* transform = new Transform(this, Vector(pos.getX(), pos.getY()), Vector::zero, width);
		new Image(this, &sdl->images().at("DIALOG_BOX"));
		BoxText* boxText = new BoxText(this, texts, widthLetter, heightLetter, letterFrequency, font, widthBox);
		height = boxText->getNumLines() * 90;
		transform->setH(height);
	}

	virtual ~Dialogue() {
		delete font;
		font = nullptr;
	}
};