#pragma once
#include "../structure/Component.h"
class Transform;
class GameObject;
class CollisionsManager;
class TriggerComp :public Component {
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_TRIGGER;

protected:
	CollisionsManager* collisionsManager_;
	Transform* transform_;
	GameObject* other_;
	bool overlap_;
public:
	TriggerComp();
	//llamado por CollisionsManager
	virtual void Overlap(GameObject* other);
	virtual void update() { }
	virtual void OnTriggerEnter() {};
	virtual void OnTriggerExit() {};
protected:


};

