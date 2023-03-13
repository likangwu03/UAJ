#pragma once
#include <string>
#include "../components/Transform.h"
#include "../structure/Component.h"
#include "../structure/GameObject.h"
#include "../sdlutils/Texture.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"

using namespace std;

class SceneManager;

class ButtonComp : public Component {
private:

	SDL_Joystick* _joy;
	Transform* transform;
	Texture* highlight;
	void (*_callback)();
	bool highlighted;
	SDL_Rect dest;
	Transform* tf;

	void playSound();

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BUTTON_COMP;

	ButtonComp(GameObject* parent, string hl, void (*callback)());
	void handleEvents() override;
	bool isHighlighted();
	void render();
};

