#pragma once
#include "TransitionScene.h"
#include "CinematicBaseScene.h"
//muestra el texto de skip de la cinem¨¢tica
class ShowSkipTransitionScene :public TransitionScene
{
private:
	CinematicBaseScene* cinematicScene;

public:
	ShowSkipTransitionScene(CinematicBaseScene* backgroundScene, float duration, bool fadeOut = false, string texture = "") :TransitionScene(nullptr, duration, fadeOut, texture), cinematicScene(backgroundScene) {};
	void render()override;
	void update() override;
	void handleEvents() override;
};

