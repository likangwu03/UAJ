#include "../Structure/GameObject.h"
#include "../Components/Transform.h"
#include "../Components/KitchenTriggerComp.h"

class KitchenSurfaceObj : public GameObject {
private:

public:
	KitchenSurfaceObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new KitchenTriggerComp(this, Vector(0, 0), w, h);
	}
};