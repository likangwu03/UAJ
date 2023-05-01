#include "HeartRender.h"

HeartRender::HeartRender(GameObject* parent, Texture* texture, int widthHeart, int heightHeart, int offsetY) :
	Component(parent, id), texture(texture), widthHeart(widthHeart), heightHeart(heightHeart),
	progressHeart(0), offsetY(offsetY), elapsedTime(0), disappearTimer(400) {
	clientState = parent->getComponent<ClientState>();
	transform = parent->getComponent<Transform>();

	currentHappiness = clientState->getHappiness();
	change = (currentHappiness / (texture->numCols() - 1)); //* 0.97;
}

void HeartRender::update() {
	// llega hasta el corazón vacío y después de un corto lapso de tiempo,
	// se autodesactiva
	if (clientState->getState() == ClientState::OUT) {
		elapsedTime += deltaTime;
		if (elapsedTime > disappearTimer) {
			elapsedTime = 0;
			setActive(false);
		}
	}

	if (progressHeart < texture->numCols() - 1 &&
		clientState->getHappiness() <= currentHappiness - change) {

		++progressHeart;
		currentHappiness -= change;
	}
}

void HeartRender::render() {
	SDL_Rect dest;
	dest.w = widthHeart;
	dest.h = heightHeart;
	dest.x = transform->getPos().getX() + transform->getW() / 3 - widthHeart / 2;
	dest.y = transform->getPos().getY() - offsetY;
	texture->renderFrame(dest, progressHeart, 0);
}