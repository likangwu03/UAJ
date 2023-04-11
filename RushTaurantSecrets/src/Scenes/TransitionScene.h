#pragma once
#include "../Structure/Scene.h"
#include "../Utilities/Texture.h"
#include "../Structure/GameManager.h"

#include "../Utilities/SDLUtils.h"
class TransitionScene : public Scene
{
private:
	Texture* filter;
	const float duration;
	float cont;
	const float WIDTH, HEIGHT;
	Scene* scene;
	int fadeOutInverter;

public:
	TransitionScene(Scene* backgroundScene, float duration, bool fadeOut = false, string texture = "");
	void render() override;
	void update() override;

};

