#pragma once
#include "../structure/Component.h"
#include <SDL_rect.h>
#include "../utilities/Vector.h"
#include "../sdlutils/InputHandler.h"
class Transform;
class GameObject;
//class CollisionsManager;

//hay que definir su posicion, considerando coordenada relativa, 
//centro es pos de transform
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
	TriggerComp(GameObject* parent, Vector pos_, float width_, float height_);
public:
	bool IsOverLap() { return overlap_; }
	SDL_FRect getRect();
	//llamado por CollisionsManager
	virtual void Overlap(GameObject* other);
	
	virtual void isOverlapping(){} //es llamado mientras haya overlap
	virtual void onTriggerEnter() {}; //solo es llamado en el momento de overlap
	virtual void onTriggerExit() {}; //solo es llamado cuando sale del overlapping
protected:


};

