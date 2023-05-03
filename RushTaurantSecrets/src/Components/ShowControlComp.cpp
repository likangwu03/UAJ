#include "ShowControlComp.h"
#include "../Utilities/checkML.h"
#include "../Structure/Scene.h"
#include "../Components/PlayerMovementController.h"
ShowControlComp::ShowControlComp(GameObject* parent, vector<ControlsInfo> controls): Component(parent, id)
{
	controls_ = vector<showControlInfo>(controls.size());
	if (!ih().joysticksInitialised()) {
		for (int i = 0; i < controls.size(); ++i) {

			controls_[i].col = Controls[controls[i].key].col;
			controls_[i].row = Controls[controls[i].key].fil;
			controls_[i].offset = controls[i].offset;
			controls_[i].height = controls[i].height;
			controls_[i].proportion = Controls[controls[i].key].proportion;
			controls_[i].texture = &sdlutils().images().at(Controls[controls[i].key].textureName);

		}
	}
	else {
		if (parent->getScene()->getGameObject(hdr_PLAYER)->getComponent<PlayerMovementController>()->isXbox()) {
			for (int i = 0; i < controls.size(); ++i) {
				controls_[i].col = Controls[controls[i].xbox].col;
				controls_[i].row = Controls[controls[i].xbox].fil;
				controls_[i].offset = controls[i].offset;
				controls_[i].height = controls[i].height;
				controls_[i].proportion = Controls[controls[i].xbox].proportion;
				controls_[i].texture = &sdlutils().images().at(Controls[controls[i].xbox].textureName);
			}
		}
		else //play
		{
			for (int i = 0; i < controls.size(); ++i) {
				controls_[i].col = Controls[controls[i].play].col;
				controls_[i].row = Controls[controls[i].play].fil;
				controls_[i].offset = controls[i].offset;
				controls_[i].height = controls[i].height;
				controls_[i].proportion = Controls[controls[i].play].proportion;
				controls_[i].texture = &sdlutils().images().at(Controls[controls[i].play].textureName);
			}
		}
	}
	setActive(false);
}

void ShowControlComp::render(Vector pos) {
	for (auto c : controls_)
		c.texture->renderFrame(build_sdlrect(pos.getX() + c.offset.getX() - ((c.height * c.proportion) / 2), pos.getY() + c.offset.getY() - c.height / 2, c.height * c.proportion, c.height), c.col, c.row, 0);
}

void ShowControlComp::changeOffset(Vector off, int i) {
	controls_[i].offset = off;
}

void ShowControlComp::changeHeight(float height,int i) {
	controls_[i].height=height;
}

Texture* ShowControlComp::getTexture(int i) {
	return controls_[i].texture;
}