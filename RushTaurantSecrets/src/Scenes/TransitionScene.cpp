#include "TransitionScene.h"
#include "../Utilities/checkML.h"

TransitionScene::TransitionScene(Scene* backgroundScene,float duration, bool fadeOut,string texture):scene(backgroundScene), cont(0),WIDTH(sdlutils().width()), HEIGHT(sdlutils().height()), duration(duration*1000) {
	if(texture=="") filter = &sdlutils().images().at("Filter_Black");
	else filter = &sdlutils().images().at(texture);
	if (fadeOut)fadeOutInverter = 0;
	else fadeOutInverter = 100;
}

void TransitionScene::render() {
	scene->render();
	filter->render(build_sdlrect(0, 0, WIDTH, HEIGHT));
}

void TransitionScene::update() {
	cont += frameTime;
	scene->update();
	filter->setOpacity(fadeOutInverter-(cont * 100/ duration));
	if (cont > duration) {
		GameManager::get()->deleteCurrentScene();
	}
}
