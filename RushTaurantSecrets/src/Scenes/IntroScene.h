#pragma once
#include "../Structure/Scene.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"
#include "../GameObjects/Player.h"
class IntroScene : public Scene
{
private:
	Texture* bg;
	Texture* filter;
	GameObject* player;
	const float WIDTH, HEIGHT;
public:
	IntroScene();
	void render () override;
	void handleEvents()override;
	void callAfterCreating() override;
};

