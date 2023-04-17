#pragma once
#include <string>
#include <functional>
#include "../Components/Transform.h"
#include "../Structure/Component.h"
#include "../Structure/GameObject.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"

using namespace std;

class SceneManager;

class ButtonComp : public Component {
private:

	SDL_Joystick* _joy;
	Transform* transform;
	Texture* highlight;
	//void (*_callback)(); // std::function<void(void)>
	std::function<void()> _callback;
	bool highlighted;
	SDL_Rect dest;
	Transform* tf;
	SoundEffect* buttonSound;
	SoundEffect* buttonHoverSound;

	bool selected;
	void playSound();

public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_BUTTON_COMP;

	ButtonComp(GameObject* parent, string hl, std::function<void()> callback);
	void handleEvents() override;
	bool isHighlighted();
	void setHighlighted(bool isH);
	void render();
};

