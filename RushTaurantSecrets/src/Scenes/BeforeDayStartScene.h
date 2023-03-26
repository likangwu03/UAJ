#include "../Structure/Scene.h"
#include "../Components/Image.h"
#include "../Managers/DayManager.h"

class BeforeDayStartScene : public Scene {
	const int OFFSET_DAY = 50;

private:
	DayManager* day;
	GameManager* gm;
	InputHandler* ih;

	GameObject* obj; //objeto para background
	GameObject* targetObj; //objeto para diana

	Font* dayText;
	Font* pressButtonText;
	Font* text;

	string wordDay;
	string press;
	string mnyTarget;

	Texture* background;
	Texture* target;
	Texture* dayTxt;
	Texture* buttonTxt;
	Texture* moneyTarget;
	
	
public:
	BeforeDayStartScene();
	~BeforeDayStartScene();
	virtual void handleEvents();
	virtual void render();
	virtual void update();
	void toDailyMenu();
};