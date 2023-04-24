#include "Text2.h"
#include "../Structure/GameObject.h"
Text2::Text2(GameObject* parent, std::string t, std::string font, SDL_Color fg, int width, int height):Component(parent,id) {
	text_ = t;
	font_ = &SDLUtils::instance()->fonts().at(font);
	fgColor = fg;
	width_ = width;
	height_ = height;
	offset = Vector();
	transform = parent->getComponent<Transform>();
	if (t == "") textTexture_ = new Texture(SDLUtils::instance()->renderer(), " ", *font_, fgColor);
	else textTexture_ = new Texture(SDLUtils::instance()->renderer(), text_, *font_, fgColor);
}


Text2::Text2(GameObject* parent, std::string t, Font* font, SDL_Color fg, int width, int height) :Component(parent, id) {
	text_ = t;
	font_ = font;
	fgColor = fg;
	width_ = width;
	height_ = height;
	offset = Vector();
	transform = parent->getComponent<Transform>();
	if (t == "") textTexture_ = new Texture(SDLUtils::instance()->renderer(), " ", *font_, fgColor);
	else textTexture_ = new Texture(SDLUtils::instance()->renderer(), text_, *font_, fgColor);
}

void Text2::setText(std::string t) {
	if (text_ != t) {
		text_ = t;
		delete textTexture_;
		if (text_ == "") textTexture_ = new Texture(SDLUtils::instance()->renderer(), " ", *font_, fgColor);
		else {
			textTexture_ = new Texture(SDLUtils::instance()->renderer(), text_, *font_, fgColor);
		}
	}
}

void Text2::render() {
	SDL_Rect dest;
	dest.x = transform->getPos().getX() + offset.getX();
	dest.y = transform->getPos().getY() + offset.getY();
	dest.w = getWidth();
	dest.h = getHeight();
	// renderiza la textura
	textTexture_->render(dest.x,dest.y);
}
