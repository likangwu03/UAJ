#include "Textbox.h"
#include "../Structure/GameObject.h"

TextBox::TextBox(GameObject* parent, string hl, int max) : Component(parent, id), highlighted(false), select_(false), MAX_CHAR(max), text(nullptr) {
	highlight = &sdlutils().images().at(hl);
	ih_ = InputHandler::get();
	text = parent->getComponent<Text2>();
	auto tf = parent->getComponent<Transform>();
	dest.x = tf->getPos().getX();
	dest.y = tf->getPos().getY();
	dest.w = tf->getW();
	dest.h = tf->getH();
}

void TextBox::handleEvents() {

	if (highlighted &&ih_->keyDownEvent()) {
		if (select_) {
			char x = ih_->getCurrentKey();
			string t;
			t = text->getText_();
			if (x == '\n') {
				select_ = false;
			}
			else if (x == '\b' && t.length() > 0) {
				t.pop_back();
			}
			else if (x != '\b' && !ih_->isKeyDown(SDLK_UP) && !ih_->isKeyDown(SDLK_DOWN) && t.length() < MAX_CHAR) {
				t.push_back(x);
			}
			text->setText(t);
		}
		else if(ih_->isKeyDown(SDL_SCANCODE_SPACE)) {
			select_ = true;
		}	
	}

}

bool TextBox::isHighlighted() {
	return highlighted;
}
void TextBox::setHighlighted(bool isH) {
	highlighted = isH;
}
void TextBox::render() {
	if (highlighted) {
		highlight->render(dest);
	}
}