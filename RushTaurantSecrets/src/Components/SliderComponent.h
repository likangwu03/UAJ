#pragma once
#include "../Structure/Component.h"
#include "../GameObjects/ButtonGO.h"

class SliderComponent : public Component
{
	enum DPAD_XBOX { UP, DOWN, RIGHT, LEFT };
private:
	ButtonGO* sliderButton;
	Image* sliderBarImage;
	GameObject* sliderBar;

	bool slider = false;

	int numSlider;
public:
	SliderComponent(GameObject* parent, Vector pos_, float width_, float height_, ButtonGO* _sliderButton, int _numSlider);

	virtual void handleEvents();
	void setSlider(bool _slider);
	bool getSlider();
};

