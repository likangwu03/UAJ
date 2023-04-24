#pragma once

#include "../Structure/Component.h"
#include <string>
#include "../Utilities/SDLUtils.h"
#include "Transform.h"

class Text2 :public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TEXT2;
private:
	std::string text_;
	Font* font_;
	Texture* textTexture_;
	int width_;
	int height_;
	SDL_Color fgColor;
	Vector offset;
	Transform* transform;

public:
	Text2(GameObject* parent, std::string t = "", std::string font = "ARIAL16", SDL_Color fg = build_sdlcolor(0x000000FF), int width = 15, int height = 20);
	Text2(GameObject* parent, std::string t , Font* font ,SDL_Color fg = build_sdlcolor(0x000000FF), int width = 50, int height = 50);
	~Text2() {
		delete textTexture_;
	}

	void setText(std::string t = "");

	std::string getText_() { return text_; }

	Texture* getTexture() { return textTexture_; }

	int getWidth() {
		return text_.size() * width_;
	}

	int getHeight() { return height_; }


	virtual void render();

	void Setoffset(Vector v) {
		offset = v;
	}
	

};