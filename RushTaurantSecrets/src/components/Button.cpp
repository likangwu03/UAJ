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
	InputHandler::instance()->initialiseJoysticks(_joy);

}
//para sprites pasando SDL_rect
Button::Button(GameObject* parent, Texture* t, SDL_Rect d, SceneManager* sceneManager, void(*callback)(SceneManager* sceneManager)) 
	: Component(parent, id), texture(t), dest(d), sceneManager(sceneManager), callback(callback), sdl(SDLUtils::instance())
{
	// se inicializa el mando
	InputHandler::instance()->initialiseJoysticks(_joy);
}

//para sprites pasando pos
Button::Button(GameObject* parent, Texture* t, int x, int y, SceneManager* sceneManager, void(*callback)(SceneManager* sceneManager))
	: Component(parent, id), texture(t), sceneManager(sceneManager), callback(callback), sdl(SDLUtils::instance())
{
	dest = { x, y, t->width(), t->height() };
	// se inicializa el mando
	InputHandler::instance()->initialiseJoysticks(_joy);
}

Button::Button(GameObject* parent, string s, int x, int y, SceneManager* sceneManager, void(*callback)(SceneManager* sceneManager))
	: Component(parent, id), sceneManager(sceneManager), callback(callback), sdl(SDLUtils::instance())
{
	texture = &((*sdl).images().at(s));
	dest = { x, y, texture->width(), texture->height() };
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