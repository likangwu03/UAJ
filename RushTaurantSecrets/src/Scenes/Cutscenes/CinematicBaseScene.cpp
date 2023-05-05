#include "CinematicBaseScene.h"

#include "../../Utilities/InputHandler.h"
#include "../../Structure/GameObject.h"
#include "../../Components/StraightMovement.h"
#include "../../Components/CharacterAnimator.h"
#include "../../Structure/Game.h"

CinematicBaseScene::CinematicBaseScene() : Scene(), cont(0), sdl(SDLUtils::instance()), WIDTH(sdlutils().width()), HEIGHT(sdlutils().height()), dialogueBox(nullptr) {
	font = new Font(FONT_PATH, FONTSIZE);
	if (ih->joysticksInitialised())
		skipText = new Texture(sdlutils().renderer(), "Press B to skip", *font, build_sdlcolor(0xffffffFF));
	else skipText = new Texture(sdlutils().renderer(), "Press ESC to skip", *font, build_sdlcolor(0xffffffFF));

	player = new GameObject(this);
	transform = new Transform(player, Vector(0, 0), 0, 48, 96, 0);
	straightMovement = new StraightMovement(player, 5);

	anim = new CharacterAnimator(player, &sdlutils().images().at("Player_1"), ANIMATIONSPARAMS);
	anim->setframeRate(10);

	net_active = false;
}

CinematicBaseScene::~CinematicBaseScene() {
	delete font;
	delete skipText;
}

void CinematicBaseScene::render() {
	Scene::render();
	renderCinematic();
	renderUI();
}

void CinematicBaseScene::renderUI() {
	if (cont < SHOW_TEXT_DURATION * 1000) {
		skipText->render(build_sdlrect(50, 50, SKIP_WIDTH, SKIP_HEIGHT));
	}
	if (dialogueBox != nullptr)
		dialogueBox->render();
}

void CinematicBaseScene::update() {
	Scene::update();
	cont += frameTime;
}

void CinematicBaseScene::finishScene() {
	if (net_active) {
		Message m;
		m.id = Message::msg_FINISH_CINEMATIC;
		Game::get()->getCoopHandler()->send(m);
	}

}

void CinematicBaseScene::handleEvents() {
	//Scene::handleEvents();
	if (dialogueBox != nullptr)
		dialogueBox->handleEvents();
	if (ih->joysticksInitialised() && ih->getButtonState(0, SDL_CONTROLLER_BUTTON_A) || !ih->joysticksInitialised() && ih->isKeyDown(SDLK_ESCAPE))
		finishScene();

}

void CinematicBaseScene::receive(const Message& message) {
	if (message.id == Message::msg_FINISH_CINEMATIC) {
		finishScene();
	}
}