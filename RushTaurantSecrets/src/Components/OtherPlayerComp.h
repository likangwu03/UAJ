#pragma once
#include "../Structure/Component.h"
#include "Transform.h"
#include "../Utilities/Texture.h"

class OtherPlayerComp : public Component {
private:
	uint8_t timer;
	Transform* myTrans, *theirTrans;
	Texture* algo;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_OTHERPLAYER;

	OtherPlayerComp(GameObject* parent);

	void update();
	void receive(const Message& message);
};