#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/TimeOfDay.h"
#include "../Utilities/SDLUtils.h"

using namespace std;

class TimeOfDayObj : public GameObject
{
public:
	TimeOfDayObj(Scene* scene, Vector pos, Texture* aftTexture, Texture* nightTexture) :GameObject(scene, _ecs::grp_HUD) {
		new Transform(this, pos);
		new TimeOfDay(aftTexture, nightTexture,this);
		scene->pushRenderList(Down, this);
	}
};