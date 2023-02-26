#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/CartelTrigger.h"
#include "../components/Image.h"
#include "../components/ButtonComp.h"
#include "../structure/Food_def.h"
#include <string>

class Scene;
class Vector;

using namespace std;

class ButtonGO : GameObject
{
public:
	ButtonGO(Scene* scene, string t, string ht, Vector pos, float w, float h, void(*callback)()) : GameObject(scene, _ecs::grp_HUD) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new Image(this, &((*SDLUtils::instance()).images().at(t)));
		new ButtonComp(this, ht, callback);
	};
};

