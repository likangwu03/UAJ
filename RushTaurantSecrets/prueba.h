#pragma once
#include "src/structure/GameObject.h"
#include "PruebaComponent.h"
#include "src/structure/Structure_def.h"
#include "src/sdlutils/SDLUtils.h"
#include "src/components/Animator.h"
#include "src/components/PlayerMovementController.h"
#include "src/components/CollisionComp.h"
class Scene;
class prueba:public GameObject
{
private:
	Texture* tex;
public:
	prueba(Scene* scene) :GameObject(scene, _ecs::grp_PLAYER) {
		auto& sdl = *SDLUtils::instance();

		//tex = &(sdl.images().at("MERMELADA"));
		//new PruebaComponent( tex, this,_ecs::cmp_IMAGE);
		new Transform(this, Vector(100,200), Vector(0, 0), 48, 96, 0);
		new PlayerMovementController(this);
		new Animator(this, &(sdl.images().at("Player_1")), 0, 6, 2);	
		new CollisionComp(this, { 0,48 },48 * sdlutils().getResizeFactor(),48 * sdlutils().getResizeFactor());
	};
};

