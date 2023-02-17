#include "CollisionsManager.h"
#include "../structure/Scene.h"

CollisionsManager::CollisionsManager(Scene* scene) :scene_(scene) {
	grp_Player = scene_->getGroup(_ecs::grp_PLAYER);
	grup_Collisions= scene_->getGroup(_ecs::grp_COLLISIONS);
	grp_Customers = scene_->getGroup(_ecs::grp_CUSTOMERS);
	grp_Interactable = scene_->getGroup(_ecs::grp_INTERACTABLE);
}


void CollisionsManager::Collision() {
	for (auto player : grp_Player){
		for (auto col : grup_Collisions) {
			//colison AABB
		}
		for (auto p : grp_Player) {
			if (player != p) {
				//colision AABB
			}
		}
	}
}
void CollisionsManager::Overlap() {
	for (auto customer : grp_Customers) {
		
	}

}