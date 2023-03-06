#include "ShooRender.h"

ShooRender::ShooRender(GameObject* parent) 
	: Component(parent, id), offsetX(-16), offsetY(-16),
	spriteWidth(16), spriteHeight(16), ih(InputHandler::instance())
{
	string tex;
	if (ih->joysticksInitialised()) {
		row = 4;
		col = 0;
		tex = "KEYBOARD_KEYS";
	}
	else {
		row = 3;
		col = 3;
		tex = "PLAYSTATION_KEYS";
	}
	texture = &sdlutils().images().at(tex);
	transform = parent->getComponent<Transform>();
	parentTransform = parent->getComponent<Transform>();

	setActive(false);
}

void ShooRender::render()
{
	SDL_Rect dest;
	dest.x = parentTransform->getPos().getX() - offsetX;
	dest.y = parentTransform->getPos().getY() + offsetY;
	dest.w = 32;
	dest.h = 32;

	texture->renderFrame(dest, col, row, 0);
}
