#pragma once
#include "ShowControlComp.h"
//renderiza seg¨²n transform del gameObject
class ShowControlAuto : public ShowControlComp
{
private:
	Transform* parentTransform;
public:
	ShowControlAuto(GameObject* parent, vector<ControlsInfo> controls, Transform* transform = nullptr);
	void render() override;
};

