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
private:
public:
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
		float height;
		int row;
		int col;
		float proportion;
		Texture* texture;
	};
protected:
	vector<showControlInfo> controls_;
	
public:
	constexpr static _ecs::_cmp_id id = _ecs::cmp_SHOWCONTROL;
	ShowControlComp(GameObject* parent, vector<ControlsInfo> controls);
	void render(Vector pos);
	void changeOffset(Vector off,int i);
	float getProportion(int i) { return controls_[i].proportion; };
	void changeHeight(float height,int i);

	Texture* getTexture(int i);
	inline vector<showControlInfo>* getControls() {
		return &controls_;
	}
};

