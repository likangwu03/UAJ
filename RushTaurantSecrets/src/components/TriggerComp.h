#pragma once
#include "../structure/Component.h"
#include <SDL_rect.h>
#include "../utilities/Vector.h"
class Transform;
class GameObject;
//class CollisionsManager;

//hay que definir su posicion, considerando coordenada relativa, 
//centro es pos de transform
class TriggerComp :public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TRIGGER;

protected:
	//CollisionsManager* collisionsManager_;
	Vector pos;
	float width;
	float height;

	Transform* transform_;
	GameObject* other_;
	bool overlap_;
public:
	TriggerComp(GameObject* parent, Vector pos_, float width_, float height_);
	bool IsOverLap() { return overlap_; }
	SDL_FRect getRect();
	//llamado por CollisionsManager
	virtual void Overlap(GameObject* other);
	virtual void OnTriggerEnter() {};
	virtual void OnTriggerExit() {};
protected:


};

