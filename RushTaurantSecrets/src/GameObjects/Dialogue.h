#pragma once
//#include "../Components/Text.h"
#include "../Components/BoxText.h"
#include "../Components/Image.h"
#include "../Components/Transform.h"
#include "../Components/ShowControlComp.h"
//#include "../Structure/GameObject.h"

#include "../Utilities/SDLUtils.h"
#include "../Utilities/checkML.h"
class Scene;
class Dialogue : public GameObject {
private:
	SDLUtils* sdl;
	int widthLetter;
	int heightLetter;
	
public:
	Dialogue(Scene* scene, Vector pos, int widthBox, float letterFrequency, Font* font, Texture* portrait, deque<string> texts) :
		GameObject(scene, _ecs::grp_HUD), sdl(SDLUtils::instance()), widthLetter(17), heightLetter(30) {

		Transform* transform = new Transform(this, Vector(pos.getX(), pos.getY()));
		new Image(this, &sdl->images().at("DIALOG_BOX"));
		new Text(this, texts, widthLetter, heightLetter, letterFrequency, font, widthBox, Vector(1.25 / 4, 90 / 4.5));
		new ShowControlComp(this, {{ControlsType::key_SPACE,ControlsType::play_Circle,ControlsType::xbox_B,Vector(0,45),40,40}});
		new BoxText(this, &sdl->images().at("DIALOG_BOX_PORTRAIT"), portrait, Vector(1.4, 90));
	}
};