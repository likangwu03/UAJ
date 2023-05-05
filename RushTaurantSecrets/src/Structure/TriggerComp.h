#pragma once
#include "../Structure/Component.h"
#include <SDL_rect.h>
#include "../Utilities/Vector.h"
#include "../Utilities/InputHandler.h"
class Transform;
class GameObject;

class TriggerComp :public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TRIGGER; 

protected:
	Vector pos;
	float width;
	float height;

	InputHandler* ih;
	Transform* transform_;
	GameObject* other_;
	
	bool overlap_;
public:
	TriggerComp(GameObject* parent, Vector pos_, float width_, float height_, _ecs::_cmp_id id = TriggerComp::id);
	bool IsOverLap() { return overlap_; }
	SDL_FRect getRect();
	virtual void Overlap(GameObject* other);
	
	virtual void isOverlapping(){} //es llamado mientras haya overlap
	virtual void onTriggerEnter() {}; //solo es llamado en el momento de overlap
	virtual void onTriggerExit() {}; //solo es llamado cuando sale del overlapping
protected:


};

