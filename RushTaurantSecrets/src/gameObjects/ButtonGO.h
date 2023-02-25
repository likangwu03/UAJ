#pragma once
#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/CartelTrigger.h"
#include "../components/Image.h"
#include "../components/DailyMenuComp.h"
#include "../structure/Food_def.h"

using namespace std;

class ButtonGO : GameObject
{
public:
	ButtonGO(Scene* scene, string t, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_HUD) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new Image(this, &((*SDLUtils::instance()).images().at(t)));
		new DailyMenuComp(this, 451, 603, _ecs::cmp_DAILYMENU);

	}
};

