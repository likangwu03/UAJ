#include "../components/TriggerComp.h"
#include "../structure/GameObject.h"

class KitchenTriggerComp : public TriggerComp {
private:
	Ingredients* ing;
	InputHandler* ih;
public:

	KitchenTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_){};
	virtual void onTriggerExit();
	virtual void isOverlapping();
};