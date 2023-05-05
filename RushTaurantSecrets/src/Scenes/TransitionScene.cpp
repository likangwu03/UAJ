#include "TransitionScene.h"
#include "../Utilities/checkML.h"

TransitionScene::TransitionScene(Scene* backgroundScene, float duration, bool fadeOut, bool skipScene, string texture) :
	scene(backgroundScene), cont(0), skipScene(skipScene), WIDTH(sdlutils().width()), HEIGHT(sdlutils().height()), duration(duration * 1000) {
	if (texture == "") filter = &sdlutils().images().at("Filter_Black");
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
	int opac = abs(fadeOutInverter - (cont / duration) * 100);
	if (opac > 100) opac = 100;
	else if (opac < 0) opac = 0;
	filter->setOpacity(opac);
	if (cont > duration) {
		if (!skipScene) {
			GameManager::get()->popScene(this, scene); //fade in, delete de transicion
			scene->render();
		}
		else GameManager::get()->skipfromTransition();//fade out,delete de 2 escenas seguidas
	}
}
