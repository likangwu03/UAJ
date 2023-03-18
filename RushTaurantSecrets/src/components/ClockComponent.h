#pragma once
#include "../structure/Component.h"
#include "../sdlutils/SDLUtils.h"
#include <string>
#include "../utilities/Vector.h"
#include "Transform.h"
#include "Image.h"

using namespace std;
using namespace _ecs;

class ClockComponent : public Component
{
private:
	// parametrizable: 1000 (cada segundo) / 10000 (cada diez segundos)
	const int TIME_CLOCK_REFRESH = 1000, ANGLE = 90, ANGLE_UPDATE = 5;
	const int ICONX = 20, ICONY = 15, ICONSIZE = 48;
	const int MAX_LAPS = 1;
	SDLUtils* sdl = SDLUtils::instance();
	float lastTime;
	int numFullClock; // número de vueltas que ha dado el reloj
	int  timeT = 0, time = 0;
	GameObject* timeText;
	GameObject* arrow;
	Scene* scene;
	Font* font;

	GameObject* createIcon(string textureName, Vector position, float width, float height, float rotation = 0,
		_ecs::_grp_id grp = _ecs::grp_GENERAL, _ecs::_hdr_id handler = _ecs::hdr_INVALID);
	GameObject* dataIcon(Texture* texture, Vector position, float width, float height, float rotation,
		_ecs::_grp_id grp, _ecs::_hdr_id handler);
public:
	ClockComponent(GameObject* parent, Scene* _scene);
	int getNumFullClock() const;
	inline bool dayHasFinished() const {
		return numFullClock >= MAX_LAPS;
	}
	void updateClock();

	virtual void update();
	virtual void render();
};