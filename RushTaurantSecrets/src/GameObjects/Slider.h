#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/SliderComponent.h"

class Slider : public GameObject 
{
private:
	const int WIDTH = 300;
	const int HEIGHT = 80;

	SliderComponent* sliderComp;
public:
	Slider(Scene* scene, int x, int y, ButtonGO* _sliderButton, int numSlider) : GameObject(scene, _ecs::grp_GENERAL, _ecs::hdr_PLAYER) {
		sliderComp = new SliderComponent(this, Vector(x,y), WIDTH, HEIGHT, _sliderButton, numSlider);
	}
};