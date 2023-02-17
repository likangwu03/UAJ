#pragma once
#include "../structure/GameObject.h"
#include "../utilities/Vector.h"
#include "../components/BinComponent.h"

using namespace std;

class Bin : public GameObject
{
public:
	Bin(Scene* scene, Vector pos) :GameObject(scene, _ecs::grp_INTERACTABLE, _ecs::hdr_BIN) {
		new BinComponent(this, pos);
	}
};