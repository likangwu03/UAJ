#include "HeartRender.h"

#include "../Utilities/checkML.h"

int HeartRender::approximateHearts(float happiness) const {
	float numFloat = happiness / (2 * 10);
	if (happiness <= 0) {
		return 0;
	}
	else if (numFloat < maxHearts) {
		return numFloat + 1;
	}
	else {
		return numHearts(happiness);
	}
}

HeartRender::HeartRender(GameObject* parent, Texture* texture, int widthHeart, int heightHeart, int offsetY, int offsetX) :
	Component(parent, id), texture(texture), widthHeart(widthHeart), heightHeart(heightHeart), posStartX(0), posStartY(0) {
	clientState = parent->getComponent<ClientState>();
	transform = parent->getComponent<Transform>();

	posStartY = -offsetY;
	posStartX = offsetX + transform->getW() / 2;
	maxHearts = numHearts(clientState->getHappiness());
	if (isPar(maxHearts)) {
		// se resta n/2 corazones
		posStartX = posStartX - (maxHearts / 2) * widthHeart;
	}
	else {
		// se resta medio corazón
		posStartX = posStartX - widthHeart / 2;
		// se resta (n-1)/2 corazones
		posStartX = posStartX - ((maxHearts - 1) / 2) * widthHeart;
	}
}

void HeartRender::update() {
	// cuando el cliente se marcha se autodesactiva
	if (clientState->getState() == ClientState::OUT) {
		setActive(false);
	}
}

void HeartRender::render() {
	SDL_Rect dest;
	dest.w = widthHeart;
	dest.h = heightHeart;
	dest.y = posStartY + transform->getPos().getY();
	int hearts = approximateHearts(clientState->getHappiness());
	for (int i = 0; i < hearts; ++i) {
		dest.x = posStartX + i * widthHeart + transform->getPos().getX();
		texture->render(dest);
	}
}