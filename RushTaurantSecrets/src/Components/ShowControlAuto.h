#pragma once
#include "ShowControlComp.h"
//renderiza segun transform del gameObject
class ShowControlAuto : public ShowControlComp
{
private:
	Transform* parentTransform;
public:
	ShowControlAuto(GameObject* parent, vector<ControlsInfo> controls, Transform* transform = nullptr);
	void render() override;
};

