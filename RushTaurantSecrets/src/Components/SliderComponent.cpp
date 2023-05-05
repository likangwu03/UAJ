#include "SliderComponent.h"
#include "../Components/Transform.h"
#include "../Structure/GameObject.h"
#include "../Structure/GameManager.h"
#include "../Components/ButtonComp.h"
#include "../Utilities/InputHandler.h"

SliderComponent::SliderComponent(GameObject* parent, Vector pos_, float width_, float height_, ButtonGO* _sliderButton, int _numSlider) : Component(parent, id) {
	sliderButton = _sliderButton;
	numSlider = _numSlider;

	sliderBar = new GameObject(parent->getScene());
	new Transform(sliderBar, { pos_.getX(),pos_.getY() }, {0,0}, width_, height_);
	sliderBarImage = new Image(sliderBar, &((*SDLUtils::instance()).images().at("SLIDER_BAR")));
}

void SliderComponent::handleEvents() {
	if (slider) {
		int offset = 10;
		auto t = sliderButton->getComponent<Transform>();
		auto tSliderBar = sliderBar->getComponent<Transform>();
		if (ih().joysticksInitialised()) {
			//ih().refresh();
			if (ih().getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_LEFT)
				|| ih().getHatState(LEFT) || ih().xvalue(0, 1) < 0) {
				if (t->getPos().getX() - offset > (tSliderBar->getPos().getX() - t->getW() / 2)) 
					t->setPos(Vector(t->getPos().getX() - offset, t->getPos().getY()));
			}
			else if (ih().getButtonState(0, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
				|| ih().getHatState(RIGHT) || ih().xvalue(0, 1) > 0) {
				if (t->getPos().getX() + offset < (tSliderBar->getPos().getX() + tSliderBar->getW() - t->getW() / 2)) 
					t->setPos(Vector(t->getPos().getX() + offset, t->getPos().getY()));
			}
		}
		else {
			if (ih().isKeyDown(SDLK_LEFT)) {
				if (t->getPos().getX() - offset > (tSliderBar->getPos().getX() - t->getW() / 2)) 
					t->setPos(Vector(t->getPos().getX() - offset, t->getPos().getY()));
			}
			else if (ih().isKeyDown(SDLK_RIGHT)) {
				if (t->getPos().getX() + offset < (tSliderBar->getPos().getX() + tSliderBar->getW() - t->getW() / 2)) 
					t->setPos(Vector(t->getPos().getX() + offset, t->getPos().getY()));
			}
		}
		sliderButton->getComponent<ButtonComp>()->moveHighlighted();
		if (numSlider == 0)
			GameManager::instance()->setMasterVolume(((t->getPos().getX() + t->getW() / 2 - tSliderBar->getPos().getX()) * 100) / tSliderBar->getW());
		else
			GameManager::instance()->setSoundEffectsVolume(((t->getPos().getX() + t->getW() / 2 - tSliderBar->getPos().getX()) * 100) / tSliderBar->getW());
		if (!(t->getPos().getX() - offset > (tSliderBar->getPos().getX() - t->getW() / 2))) {
			if (numSlider == 0)
				GameManager::instance()->setMasterVolume(0);
			else
				GameManager::instance()->setSoundEffectsVolume(0);
		}
	}	
}

void SliderComponent::setSlider(bool _slider) {
	slider = _slider;
}

bool SliderComponent::getSlider() {
	return slider;
}