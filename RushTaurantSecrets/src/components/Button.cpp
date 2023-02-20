#include "../components/Button.h"
#include "../structure/SceneManager.h"
#include "../structure/Scene.h"
#include<SDL.h>


Button::Button(GameObject* parent, SceneManager* sceneManager, void (*callback)(SceneManager* sceneManager)) 
	: Component(parent, id), sceneManager(sceneManager), callback(callback) {
	texture = new Texture(sdlutils().renderer(), "./assets/Sprites/UI/PlayButton.png", 2, 2);
	dest = { (1280 / 2) - (BUTTON_W * 4 / 2), 400, BUTTON_W * 4, BUTTON_H * 4 };

	// se inicializa el mando
	InputHandler::instance()->initialiseJoysticks(_joy);

}

Button::~Button() {
	delete texture;
}

void Button::render() {
	src = { BUTTON_W * frame, BUTTON_H, BUTTON_W, BUTTON_H };
	texture->render(src, dest);
}

void Button::handleEvents() {
	int x, y;		// corrdenadas del puntero del ratón
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 1, 1 };

	

	if (SDL_HasIntersection(&mouseRect, &dest)) {
		frame = 1;
		if (InputHandler::instance()->getMouseButtonState(InputHandler::instance()->LEFT)) {
			callback(sceneManager);
		}
	}
	else if (InputHandler::instance()->joysticksInitialised()) {
		if (InputHandler::instance()->getButtonState(0,SDL_CONTROLLER_BUTTON_A)) {
			frame = 1;
			InputHandler::instance()->clean();
			callback(sceneManager);
		}		
	}
	else frame = 0;
}