#include "ShowControlAuto.h"
#include "../Utilities/checkML.h"
#include "../Structure/Scene.h"

ShowControlAuto::ShowControlAuto(GameObject* parent, vector<ControlsInfo> controls, Transform* transform): ShowControlComp(parent,controls)
{
	if (transform == nullptr) parentTransform = parent->getComponent<Transform>();
	else parentTransform = transform;
}

void ShowControlAuto::render()
{
	for (auto c : controls_)
		c.texture->renderFrame(build_sdlrect(parentTransform->getPos().getX() + c.offset.getX()- (c.height*c.proportion)/2, parentTransform->getPos().getY() + c.offset.getY() - c.height / 2, c.height*c.proportion, c.height), c.col, c.row, 0);
}
