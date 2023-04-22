#pragma once
#include "Transform.h"
#include "Image.h"
#include "../Utilities/InputHandler.h"
#include "../Structure/Component.h"
#include "../Definitions/Structure_def.h"
#include "../Definitions/Controls_def.h"
#include "../Utilities/Texture.h"
#include "../Utilities/SDLUtils.h"
#include "../Structure/GameObject.h";

using namespace _ecs;
using namespace std;
class ShowControlComp :public Component
{

	struct ControlsInfo {
		ControlsType key;
		ControlsType play;
		ControlsType xbox;
		Vector offset;
		float width;
		float height;
	};
	struct showControlInfo
	{
		Vector offset;
		float width;
		float height;
		int row;
		int col;
		Texture* texture;
	};
	vector<showControlInfo> controls_;
	Transform* parentTransform;
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SHOO_RENDER;
	ShowControlComp(GameObject* parent, Transform* transform, vector<ControlsInfo> controls);
	void render() override;
};

