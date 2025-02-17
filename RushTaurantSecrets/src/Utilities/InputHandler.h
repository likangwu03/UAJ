// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL.h>
#include <array>
#include <vector>
#include "../Utilities/Vector.h"
#include "../Utilities/Singleton.h"

// Instead of a Singleton class, we could make it part of
// SDLUtils as well.

const int JOYSTICK_DEAD_ZONE = 10000;

class InputHandler : public Singleton<InputHandler> {

	friend Singleton<InputHandler>;

public:
	enum MOUSEBUTTON : uint8_t {
		LEFT = 0, MIDDLE = 1, RIGHT = 2
	};

	virtual ~InputHandler() {
	}

	// clear the state
	inline void clearState() {
		isCloseWindoEvent_ = false;
		isKeyDownEvent_ = false;
		isKeyUpEvent_ = false;
		isMouseButtonEvent_ = false;
		isMouseMotionEvent_ = false;
		for (auto i = 0u; i < 3; i++) {
			mbState_[i] = false;
		}
	}

	// update the state with a new event
	inline void update(const SDL_Event& event) {
		switch (event.type) {
		case SDL_CONTROLLERDEVICEADDED:
			initialiseJoysticks();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			clean();
			break;
		case SDL_JOYBUTTONDOWN:
			joybuttonDownEvent(event);
			break;
		case SDL_JOYBUTTONUP:
			joybuttonUpEvent(event);
			break;
		case SDL_JOYAXISMOTION:
			joystickEvent(event);	
			break;
		case SDL_KEYDOWN:
			currentKey = event.key.keysym.sym;
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		case SDL_WINDOWEVENT:
			handleWindowEvent(event);
			break;
		case SDL_JOYHATMOTION:
			joyhatEvent(event);
		default:
			break;
		}
	}

	// set keyboard/controller
	inline void setControls(bool _control) {
		control = _control;
	}

	inline bool getControls() {
		return control;
	}

	// return joystick 
	inline SDL_Joystick* getPlayerController(int player) {
		return joys[player];
	}

	// refresh
	inline void refresh() {
		SDL_Event event;

		clearState();
		while (SDL_PollEvent(&event))
			update(event);
	}

	// close window event
	inline bool closeWindowEvent() {
		return isCloseWindoEvent_;
	}

	// keyboard
	inline bool keyDownEvent() {
		return isKeyDownEvent_;
	}

	inline bool keyUpEvent() {
		return isKeyUpEvent_;
	}

	inline bool isKeyDown(SDL_Scancode key) {
		return keyDownEvent() && kbState_[key] == 1;
	}

	inline bool isKeyDown(SDL_Keycode key) {

		return isKeyDown(SDL_GetScancodeFromKey(key));
	}

	inline bool isKeyUp(SDL_Scancode key) {
		return keyUpEvent() && kbState_[key] == 0;
	}

	inline bool isKeyUp(SDL_Keycode key) {
		return isKeyUp(SDL_GetScancodeFromKey(key));
	}

	inline char getCurrentKey() { return currentKey; }

	// mouse
	inline bool mouseMotionEvent() {
		return isMouseMotionEvent_;
	}

	inline bool mouseButtonEvent() {
		return isMouseButtonEvent_;
	}

	inline const std::pair<Sint32, Sint32>& getMousePos() {
		return mousePos_;
	}

	inline int getMouseButtonState(MOUSEBUTTON b) {
		return mbState_[b];
	}

	// controller (mando)

	inline bool joyButtonDown() {
		return isControllerButtonDown;
	}

	inline bool joyButtonUp() {
		return isControllerButtonDown;
	}

	int numButtons() {
		return numB;
	}

	bool getButtonState(int joy, int buttonNumber)
	{
		bool state = m_buttonStates[joy][buttonNumber];
		if (m_buttonStates[joy][buttonNumber])
			m_buttonStates[joy][buttonNumber] = false;
		return state;
	}

	bool getHatStateMenu(int i) {
		bool state = m_joyhat[i];
		if (m_joyhat[i])
			m_joyhat[i] = false;
		return state;
	}

	bool getHatState(int i) {
		return m_joyhat[i];
	}

	bool getHatEvent() {
		return isHatEvent;
	}

	void setFalseJoyhat() {
		for (auto i : m_joyhat) 
			i = false;
		isHatEvent = false;			
	}

	int xvalue(int joy, int stick)
	{
		if (m_joystickValues.size() > 0)
		{
			if (stick == 1)
			{
				return m_joystickValues[joy].first->getX();
			}
			else if (stick == 2)
			{
				return m_joystickValues[joy].second->getX();
			}
		}
		return 0;
	}

	int yvalue(int joy, int stick)
	{
		if (m_joystickValues.size() > 0)
		{
			if (stick == 1)
			{
				return m_joystickValues[joy].first->getY();
			}
			else if (stick == 2)
			{
				return m_joystickValues[joy].second->getY();
			}
		}
		return 0;
	}

	void initialiseJoysticks() {
		int numButtons = 5;
		bool joyInit = false;
		if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
		{
			SDL_InitSubSystem(SDL_INIT_JOYSTICK);
		}
		int joysticks = SDL_NumJoysticks();
		if (joysticks > 0)
		{
			for (int i = 0; i < joysticks; i++)
			{
				SDL_Joystick* joy = SDL_JoystickOpen(i);
				joys.push_back(joy);
				if (SDL_JoystickGetAttached(joy) == 1) // nueva alternativa a SDL_JoystickOpened a partir de SDL 2.0
				{
					if (SDL_JoystickNumButtons(joy) > numButtons) {
						joyInit = true;
						m_joysticks.push_back(joy);
						m_joystickValues.push_back(std::make_pair(new
							Vector(0, 0), new Vector(0, 0))); // add our pair
						std::vector<bool> cButtons;
						for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
						{
							numB++;
							cButtons.push_back(false);
						}
						m_buttonStates.push_back(cButtons);
					}		
				}
				else
				{
					std::cout << SDL_GetError();
				}
			}
			SDL_JoystickEventState(SDL_ENABLE);

			m_bJoysticksInitialised = joyInit;

			control = false;
			
			std::cout << "Initialised " << m_joysticks.size() << " joystick(s)\n";
		}
		else
		{
			m_bJoysticksInitialised = false;
		}
	}

	bool joysticksInitialised() {
		return m_bJoysticksInitialised;
	}

	void clean()
	{
		if (m_bJoysticksInitialised)
		{
			for (auto it : m_joysticks) {
				SDL_JoystickClose(it);
				m_joysticks.pop_back();
				//joys.pop_back();
				//m_buttonStates.pop_back();
			}
		}
		m_bJoysticksInitialised = false;
	}

	void setXBox(bool _xbox) {
		xbox = _xbox;
	}

	bool getXBox() {
		return xbox;
	}

	inline SDL_Joystick* rJoystick() {
		return joys[0];
	}

private:

	InputHandler() {
		kbState_ = SDL_GetKeyboardState(0);
		clearState();
	}

	inline void onKeyDown(const SDL_Event&) {
		isKeyDownEvent_ = true;
	}

	inline void onKeyUp(const SDL_Event&) {
		isKeyUpEvent_ = true;
	}

	inline void onMouseMotion(const SDL_Event& event) {
		isMouseMotionEvent_ = true;
		mousePos_.first = event.motion.x;
		mousePos_.second = event.motion.y;
	}

	inline void onMouseButtonChange(const SDL_Event& event, bool isDown) {
		isMouseButtonEvent_ = true;
		switch (event.button.button) {
		case SDL_BUTTON_LEFT:
			mbState_[LEFT] = isDown;
			break;
		case SDL_BUTTON_MIDDLE:
			mbState_[MIDDLE] = isDown;
			break;
		case SDL_BUTTON_RIGHT:
			mbState_[RIGHT] = isDown;
			break;
		default:
			break;
		}
	}

	inline void handleWindowEvent(const SDL_Event& event) {
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			isCloseWindoEvent_ = true;
			break;
		default:
			break;
		}
	}

	inline void joyhatEvent(const SDL_Event& event) {
		isHatEvent = true;
		if (event.jhat.value == SDL_HAT_UP)
		{
			m_joyhat[0] = true;
		}
		if (event.jhat.value == SDL_HAT_DOWN)
		{
			m_joyhat[1] = true;
		}
		if (event.jhat.value == SDL_HAT_RIGHT)
		{
			m_joyhat[2] = true;
		}
		if (event.jhat.value == SDL_HAT_LEFT)
		{
			m_joyhat[3] = true;
		}
		if (event.jhat.value == SDL_HAT_CENTERED) {
			setFalseJoyhat();
		}
	}

	inline void joyhatState() {
		
	}

	inline void joybuttonDownEvent(const SDL_Event& event) {
		if (event.type == SDL_JOYBUTTONDOWN)
		{
			isControllerButtonDown = true;
			int whichOne = event.jaxis.which;
			m_buttonStates[whichOne][event.jbutton.button] = true;
		}
	}	

	inline void joybuttonUpEvent(const SDL_Event& event) {
		if (event.type == SDL_JOYBUTTONUP)
		{
			isControllerButtonUp = true;
			int whichOne = event.jaxis.which;
			m_buttonStates[whichOne][event.jbutton.button] = false;
		}
	}

	inline void joystickEvent(const SDL_Event& event) {
		int whichOne = event.jaxis.which;
		// left stick move left or right
		if (event.jaxis.axis == 0)
		{
			if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
			{
				m_joystickValues[whichOne].first->setX(1);
			}
			else if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
			{
				m_joystickValues[whichOne].first->setX(-1);
			}
			else
			{
				m_joystickValues[whichOne].first->setX(0);
			}
		}
		// left stick move up or down
		if (event.jaxis.axis == 1)
		{
			if (event.jaxis.value > JOYSTICK_DEAD_ZONE)
			{
				m_joystickValues[whichOne].first->setY(1);
			}
			else if (event.jaxis.value < -JOYSTICK_DEAD_ZONE)
			{
				m_joystickValues[whichOne].first->setY(-1);
			}
			else
			{
				m_joystickValues[whichOne].first->setY(0);
			}
		}
	}

	int numB = 0;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector*, Vector*>> m_joystickValues;
	std::vector<std::vector<bool>> m_buttonStates;
	bool m_bJoysticksInitialised = false;

	bool isHatEvent = false;
	std::vector<bool> m_joyhat {false, false, false, false};

	bool control = true; // true teclado false mando

	std::vector<SDL_Joystick*> joys;

	bool isCloseWindoEvent_;
	bool isKeyUpEvent_;
	bool isKeyDownEvent_;
	bool isMouseMotionEvent_;
	bool isMouseButtonEvent_;
	bool isControllerEventX;
	bool isControllerEventY;
	bool isControllerButtonDown;
	bool isControllerButtonUp;
	float controllerI;
	std::pair<Sint32, Sint32> mousePos_;
	std::array<bool, 3> mbState_;
	const Uint8* kbState_;
	char currentKey;

	bool xbox = false;
};

// This macro defines a compact way for using the singleton InputHandler, instead of
// writing ih().method() we write ih().method()
//
inline InputHandler& ih() {
	return *InputHandler::instance();
}
