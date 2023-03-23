#include "MurderRender.h"
#include "../Utilities/checkML.h"

MurderRender::MurderRender(GameObject* parent)
	: Component(parent, id), offsetX(-16), offsetY(-16),
	spriteWidth(16), spriteHeight(16), ih(InputHandler::instance())
{
	string tex;
	if (!ih->joysticksInitialised()) {
		row = 2;
		col = 4;
		tex = "KEYBOARD_KEYS";
	}
	else {
		row = 4;
		col = 3;
		tex = "PLAYSTATION_KEYS";
	}
	texture = &sdlutils().images().at(tex);
	transform = parent->getComponent<Transform>();
	parentTransform = parent->getComponent<Transform>();

	setActive(false);
}

void MurderRender::render()
{
	SDL_Rect dest;
	dest.x = parentTransform->getPos().getX() - offsetX;
	dest.y = parentTransform->getPos().getY() + offsetY;
	dest.w = 32;
	dest.h = 32;

	texture->renderFrame(dest, col, row, 0);
}
