#include "DailyMenuScene.h"
#include "SuperMarket.h"
#include "../utils/checkML.h"
#include "../structure/SceneManager.h"

void DailyMenuScene::select(SceneManager* sceneManager)
{
	sceneManager->ChangeScene(SceneManager::SUPERMARKET);
}

DailyMenuScene::DailyMenuScene(SceneManager* sceneManager, uint8_t msize, bool m) : sdl(SDLUtils::instance())
{
	ButtonGO* dailyMenu1 = new ButtonGO(this, "DAILY_MENU", Vector(sdl->width() / 2, sdl->height() / 15), 451, 603);

	//ButtonGO* dailyMenu2 = new ButtonGO(this, Vector(sdl->width() / 2, sdl->height() / 15), 451, 603);
}

void DailyMenuScene::handleEvents() {
	int x, y;		// corrdenadas del puntero del ratón
	SDL_GetMouseState(&x, &y);
	SDL_Rect mouseRect = { x, y, 1, 1 };



	//if (SDL_HasIntersection(&mouseRect, &dest)) {
	//	frame = 1;
	//	if (InputHandler::instance()->getMouseButtonState(InputHandler::instance()->LEFT)) {
	//		callback(sceneManager);
	//	}
	//}
	//else if (InputHandler::instance()->joysticksInitialised()) {
	//	if (InputHandler::instance()->getButtonState(0, SDL_CONTROLLER_BUTTON_A)) {
	//		frame = 1;
	//		InputHandler::instance()->clean();
	//		callback(sceneManager);
	//	}
	//}
	//else frame = 0;
}
