#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/CollisionComp.h"
#include "../sdlutils/SDLUtils.h"

class Scene;
class CollisionObject :public GameObject {
public:
	CollisionObject(Scene* scene,Vector pos,float w,float h) :GameObject(scene, _ecs::grp_COLLISIONS) {
		new Transform(this, pos, { 0,0 }, w, h);
	}
	//para ver como esta los colisiones 
	/*void render() {
		Transform* t = getComponent<Transform>();
		SDL_Rect aux = { t->getPos().getX(),t->getPos().getY(),t->getW(),t->getH() };
		sdlutils().images().at("24_Ice_Cream_Shop_48x48").render(aux);
	}*/
};