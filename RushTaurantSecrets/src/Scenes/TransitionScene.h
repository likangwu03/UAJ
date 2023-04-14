#pragma once
#include "../Structure/Scene.h"
#include "../Utilities/Texture.h"
#include "../Structure/GameManager.h"

#include "../Utilities/SDLUtils.h"
class TransitionScene : public Scene
{
private:
	Scene* scene;
protected:
	Texture* filter;
	const float duration;
	float cont;
	const float WIDTH, HEIGHT;
	int fadeOutInverter;
	bool skipScene;
public:
	TransitionScene(Scene* backgroundScene, float duration, bool fadeOut = false,bool skipScene=false, string texture = "");
	virtual void render() override;
	virtual void update() override;

};

