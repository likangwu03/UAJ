#include "CinematicBaseScene.h"
#include "../Utilities/InputHandler.h"

CinematicBaseScene::CinematicBaseScene() :Scene(),cont(0) {

	font = new Font(FONT_PATH, FONTSIZE);
	if (ih->joysticksInitialised())
		skipText = new Texture(sdlutils().renderer(), "Press B to skip", *font, build_sdlcolor(0xffffffFF));
	else skipText = new Texture(sdlutils().renderer(), "Press ESC to skip", *font, build_sdlcolor(0xffffffFF));

}

CinematicBaseScene::~CinematicBaseScene() {
	delete font;
	delete skipText;
}

void CinematicBaseScene::render() {
	Scene::render();
	renderCinematic();
	renderSkipText();
}

void CinematicBaseScene::renderSkipText() {
	if (cont < SHOW_TEXT_DURATION*1000) {
		skipText->render(build_sdlrect(50,50, SKIP_WIDTH,SKIP_HEIGHT));
	}
}

void CinematicBaseScene::update() {
	Scene::update();
	cont += frameTime;
}


void CinematicBaseScene::handleEvents() {
	//Scene::handleEvents();
	if (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_B) || !ih->joysticksInitialised() && ih->isKeyDown(SDLK_ESCAPE))
		finishScene();

}