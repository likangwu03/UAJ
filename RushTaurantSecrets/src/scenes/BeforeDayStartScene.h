#include "../structure/Scene.h"
#include "../components/Image.h"


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