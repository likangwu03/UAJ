#pragma once
#include "../Structure/Component.h"
#include "../GameObjects/ButtonGO.h"

class SliderComponent : public Component
{
private:
	ButtonGO* sliderButton;
	Image* sliderBarImage;
	GameObject* sliderBar;

	bool slider = false;
public:
	SliderComponent(GameObject* parent, Vector pos_, float width_, float height_, ButtonGO* _sliderButton);

	virtual void handleEvents();
	void setSlider(bool _slider);
	bool getSlider();
};

