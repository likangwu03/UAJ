#include "../structure/GameObject.h"
#include "../components/Transform.h"
#include "../components/KitchenTriggerComp.h"

class KitchenSurfaceObj : public GameObject {
private:

public:
	KitchenSurfaceObj(Scene* scene, Vector pos, float w, float h) : GameObject(scene, _ecs::grp_INTERACTABLE) {
		new Transform(this, pos, Vector(0, 0), w, h);
		new KitchenTriggerComp(this, pos, w, h);
	}
};