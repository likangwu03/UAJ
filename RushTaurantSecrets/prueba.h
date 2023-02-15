#pragma once
#include "src/structure/GameObject.h"
#include "PruebaComponent.h"
#include "src/structure/Structure_def.h"
#include "src/sdlutils/SDLUtils.h"
#include "src/components/Animator.h"
#include "src/components/PlayerMovementController.h"

class Scene;
class prueba:public GameObject
{
private:
	Texture* tex;
public:
	prueba(Scene* scene) :GameObject(scene) {
		auto& sdl = *SDLUtils::instance();

		//tex = &(sdl.images().at("MERMELADA"));
		//new PruebaComponent( tex, this,_ecs::cmp_IMAGE);

		new Animator(this, &(sdl.images().at("Player_run")), 6);
		new Transform(this, Vector(100, 100), Vector(0, 0), 20, 20, 0);
		//new PlayerMovementController(this, 2);	
	};
};

