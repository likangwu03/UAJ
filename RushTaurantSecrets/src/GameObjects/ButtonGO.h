#pragma once
#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/CartelTrigger.h"
#include "../Components/Image.h"
#include "../Components/ButtonComp.h"
#include "../Definitions/Food_def.h"
#include <string>

class Scene;
class Vector;

using namespace std;

class ButtonGO : public GameObject
{
public:
	ButtonGO(Scene* scene, string t, string ht, Vector pos, float w, float h, std::function<void()>&& callback) : GameObject(scene, _ecs::grp_HUD) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new Image(this, &((*SDLUtils::instance()).images().at(t)));
		new ButtonComp(this, ht, callback);
	};
};

