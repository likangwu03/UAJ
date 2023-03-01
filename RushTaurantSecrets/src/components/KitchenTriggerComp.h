#include "../components/TriggerComp.h"
#include "Ingredients.h"


class KitchenTriggerComp : public TriggerComp {
private:
	Ingredients* ing;
public:

	KitchenTriggerComp(GameObject* parent, Vector pos_, float width_, float height_) : TriggerComp(parent, pos_, width_, height_) {
	};
	virtual void onTriggerExit();
};