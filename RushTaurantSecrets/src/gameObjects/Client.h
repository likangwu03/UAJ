#pragma once
#include "../structure/GameObject.h"
#include "../components/CharacterAnimator.h"
#include "../components/StraightMovement.h"
#include "../components/ClientState.h"
#include "../structure/Food_def.h"
#include "../components/ClientMovement.h"
#include "../components/ClientTrigger.h"


class Client : public GameObject {
public:
	Client(Scene* scene, string sprite, Vector origin, vector<_ecs::_dish_id> menu, int posEntrance, float speed) : GameObject(scene, _ecs::grp_CLIENTS) {
		auto sdl = SDLUtils::instance();
		Transform* t = new Transform(this, origin, Vector(0, 0), 48, 96);
		new CharacterAnimator(this, &((*sdl).images().at(sprite)), 0, 6, 1);
		new StraightMovement(this, speed);
		new ClientState(this, menu);
		new ClientMovement(this, posEntrance);
		new ClientTrigger(this, Vector(0, 0), 48, 96);
	}
};