#pragma once
#include "../Structure/Component.h"
#include "../Utilities/SDLUtils.h"
#include "../Utilities/InputHandler.h"
#include "Transform.h"
#include "Text2.h"

class TextBox :public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TEXTBOX;
private:
	Texture* highlight;
	bool highlighted;
	Text2* text;
	InputHandler* ih_;
	bool select_;
	int MAX_CHAR;
	SDL_Rect dest;

public:
	TextBox(GameObject* parent, string hl, int max = 15);
	void initComponent() override;

	void handleEvents() override;
	bool isHighlighted();
	void setHighlighted(bool isH);
	void render();

};