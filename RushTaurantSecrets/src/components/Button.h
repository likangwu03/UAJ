#pragma once

#include "../structure/Component.h"
#include "../sdlutils/Texture.h"

class SceneManager;
class Scene;

static const int BUTTON_W = 96, BUTTON_H = 32;

class Button : public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BUTTON;

	Button(GameObject* parent, SceneManager* sceneManager, void (*callback)(SceneManager* sceneManager));
	~Button();
	void render();
	void handleEvents();

private:
	void (*callback)(SceneManager* sceneManager);

	int frame = 0;

	Texture* texture;
	SDL_Rect src, dest;

	SceneManager* sceneManager;
};
