#pragma once
#include "../structure/GameObject.h"
#include "../components/ClientState.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Animator.h"
#include "../sdlutils/Texture.h"

class Client : public GameObject {
public:
	Client(Scene* scene) : GameObject(scene) {
		auto& sdl = *SDLUtils::instance();
		new Animator(this, &(sdl.images().at("Customer_2")), 18, 24, 2);
		new Transform(this, Vector(100, 100), Vector(0, 0), 20, 20, 0);

		//new ClientState(this);
	}
};