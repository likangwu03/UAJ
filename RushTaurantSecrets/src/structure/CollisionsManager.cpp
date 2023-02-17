#include "CollisionsManager.h"
#include "../structure/Scene.h"
#include "../structure/GameObject.h"
#include "../components/CollisionComp.h"
#include "../components/TriggerComp.h"

CollisionsManager::CollisionsManager(Scene* scene) :scene_(scene) {
	grp_Player = scene_->getGroup(_ecs::grp_PLAYER);
	grup_Collisions= scene_->getGroup(_ecs::grp_COLLISIONS);
	grp_Customers = scene_->getGroup(_ecs::grp_CLIENTS);
	grp_Interactable = scene_->getGroup(_ecs::grp_INTERACTABLE);
}

void CollisionsManager::update() {
	Collision();
	Overlap();
}

void CollisionsManager::Collision() {
	for (auto player : grp_Player){
		CollisionComp* objCol=player->getComponent<CollisionComp>();
		SDL_FRect playerRect = objCol->getRect();
		for (auto col : grup_Collisions) {
			SDL_FRect colRect = col->getComponent<CollisionComp>()->getRect();
			if (SDL_HasIntersectionF(&playerRect,&colRect)) {
				objCol->Collision(col);
			}
		}
		for (auto p : grp_Player) {
			if (player != p) {
				SDL_FRect pRect = p->getComponent<CollisionComp>()->getRect();
				if (SDL_HasIntersectionF(&playerRect, &pRect)) {
					objCol->Collision(p);
				}
			}
		}
	}
}
void CollisionsManager::Overlap() {
	for (auto player : grp_Player) {
		CollisionComp* objCol = player->getComponent<CollisionComp>();
		SDL_FRect playerRect = objCol->getRect();
		for (auto customer : grp_Customers) {
			TriggerComp* customerTrigger = customer->getComponent<TriggerComp>();
			SDL_FRect customerRect = customerTrigger->getRect();
			if (SDL_HasIntersectionF(&playerRect, &customerRect)){
				customerTrigger->Overlap(player);
			}
			else {
				customerTrigger->Overlap(nullptr);
			}
		}
		for (auto interactive : grp_Interactable) {
			TriggerComp* interactiveTrigger = interactive->getComponent<TriggerComp>();
			SDL_FRect interactiveRect = interactiveTrigger->getRect();
			if (SDL_HasIntersectionF(&playerRect, &interactiveRect)) {
				interactiveTrigger->Overlap(player);
			}
			else {
				interactiveTrigger->Overlap(nullptr);
			}
		}
	}
	

}