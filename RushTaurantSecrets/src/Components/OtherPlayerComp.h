#pragma once
#include "../Structure/Component.h"
#include "Transform.h"
#include "../Utilities/Texture.h"

class OtherPlayerComp : public Component {
private:
	uint8_t timer, scene;
	Transform* myTrans, *theirTrans;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_OTHERPLAYER;

	OtherPlayerComp(GameObject* parent, uint8_t scene);

	void update();
	void receive(const Message& message);
};