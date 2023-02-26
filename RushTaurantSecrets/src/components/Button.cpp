#include "../components/Button.h"
#include "../structure/SceneManager.h"
#include "../structure/Scene.h"
#include<SDL.h>

#include "../utils/checkML.h"

//para spritesheets
Button::Button(GameObject* parent, SceneManager* sceneManager, void (*callback)(SceneManager* sceneManager)) 
	: Component(parent, id), sceneManager(sceneManager), callback(callback), sdl(SDLUtils::instance()) {
	texture = new Texture(sdlutils().renderer(), "./assets/Sprites/UI/PlayButton.png", 2, 2);
	//parte de la pantalla donde se pinta
	dest = { (1280 / 2) - (texture->width() * 2 / 2), 400, texture->width() * 2, texture->height() * 2 };

	// se inicializa el mando
	ih().initialiseJoysticks(_joy);

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
		if (ih().getMouseButtonState(ih().LEFT)) {
			callback(sceneManager);
		}
	}
	else if (ih().joysticksInitialised()) {
		if (ih().getButtonState(0,SDL_CONTROLLER_BUTTON_A)) {
			frame = 1;
			ih().clean();
			callback(sceneManager);
		}		
	}
	else frame = 0;
}