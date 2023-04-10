#pragma once

#include "../Scenes/UIRestaurant.h"
#include "../Structure/TriggerComp.h"
#include "../Structure/GameObject.h"
#include "../Managers/Money.h"
#include "../Managers/ClientsManager.h"
#include "Image.h"
#include "../Structure/GameManager.h"
#include "Streak.h"

/*encargada de detectar la entrada del jugador*/
class PlayerMovementController;
class Image;
class CashRegisterTrigger :public TriggerComp
{
private:
	ClientsManager* cM;
	Money* money;
	Image* highlight;
	list<Client*>* list;
	Streak* streak;
	SoundEffect* cashSound1;
	SoundEffect* cashSound2;
	SoundEffect* tipSound;
	SoundEffect* addSound; //reputation
	
	const string FONT_PATH = "assets/Fonts/EpilepsySansBold.ttf";
	const float MOVEMENT = 0.005, FONTSIZE = 25, ENDY = 230, OUT_OFFSET = 2;
	Font* font;
	Texture* tipTexture;
	Texture* bgTexture;
	bool tipped;
	const SDL_Rect INITRECT = { 865, 260, 50, 51};
	SDL_Rect currRect, bgRect;

public:
	CashRegisterTrigger(GameObject* parent, Vector pos_, float width_, float height_);
	~CashRegisterTrigger();

	virtual void isOverlapping();
	virtual void onTriggerExit();
	void render();
};

