#pragma once
#include "../structure/Component.h"
#include "../structure/Structure_def.h"
#include "../structure/GameObject.h";
using namespace std;
class AddRenderList : public Component {
public:
	enum Pos { Top, Middle, Down };
	constexpr static _ecs::_cmp_id id = _ecs::cmp_RENDER_LIST;
	AddRenderList(GameObject* parent, Pos pos):Component(parent,id) {
		//parent->getScene().
	}
};