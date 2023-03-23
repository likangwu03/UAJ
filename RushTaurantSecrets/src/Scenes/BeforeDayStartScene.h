#include "../Structure/Scene.h"
#include "../Components/Image.h"


class BeforeDayStartScene : public Scene {
private:
	Image* initialText;
	Image* moneyTarget;
	
public:
	BeforeDayStartScene();
	~BeforeDayStartScene();
	void handleEvents();
	void render();
};