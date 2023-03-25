#include "CollisionsManager.h"
#include "../Structure/Scene.h"
#include "../Utilities/checkML.h"

CollisionsManager::CollisionsManager(Scene* scene) :scene_(scene) {
	grp_Player = scene_->getGroup(_ecs::grp_PLAYER);
	grup_Collisions = scene_->getGroup(_ecs::grp_COLLISIONS);
	grp_Clients = scene_->getGroup(_ecs::grp_CLIENTS);
	grp_Interactable = scene_->getGroup(_ecs::grp_INTERACTABLE);
	grp_Desk = scene_->getGroup(_ecs::grp_DESK);
	grp_Thiefs = scene_->getGroup(_ecs::grp_THIEFS);
}


void CollisionsManager::update() {
	collision();
	overlap();
}

void CollisionsManager::collision() {
	for (auto player : *grp_Player) {
		CollisionComp* objCol = player->getComponent<CollisionComp>();
		if (objCol != nullptr) {
			Vector dir = player->getComponent<Transform>()->getVel();
			SDL_FRect playerRect = objCol->getRect();
			playerRect.x += dir.getX();
			playerRect.y += dir.getY();
			// cleon: recordad la cach <3
			for (auto col : *grup_Collisions) {
				Transform* colT = col->getComponent<Transform>();
				SDL_FRect colRect = { colT->getPos().getX(),colT->getPos().getY(),colT->getW(),colT->getH() };
				if (SDL_HasIntersectionF(&playerRect, &colRect)) {
					objCol->Collision(col);
				}
			}
			for (auto p : *grp_Player) {
				if (player != p) {
					SDL_FRect pRect = p->getComponent<CollisionComp>()->getRect();
					if (SDL_HasIntersectionF(&playerRect, &pRect)) {
						objCol->Collision(p);
					}
				}
			}
		}

	}
}
void CollisionsManager::overlap() {
	for (auto player : *grp_Player) {


		CollisionComp* objCol = player->getComponent<CollisionComp>();
		if (objCol != nullptr&&objCol->isActive()) {

			SDL_FRect playerRect = objCol->getRect();
			for (auto client : *grp_Clients) {
				TriggerComp* clientTrigger = client->getComponent<TriggerComp>();
				if (clientTrigger != nullptr) {
					SDL_FRect clientRect = clientTrigger->getRect();
					if (SDL_HasIntersectionF(&playerRect, &clientRect)) {
						clientTrigger->Overlap(player);
					}
					else {
						clientTrigger->Overlap(nullptr);
					}
				}
			}
			for (auto interactive : *grp_Interactable) {
				TriggerComp* interactiveTrigger = interactive->getComponent<TriggerComp>();
				if (interactiveTrigger != nullptr) {
					SDL_FRect interactiveRect = interactiveTrigger->getRect();
					if (SDL_HasIntersectionF(&playerRect, &interactiveRect)) {
						interactiveTrigger->Overlap(player);
					}
					else {
						interactiveTrigger->Overlap(nullptr);
					}
				}
			}
			for (auto interactive : *grp_Desk) {
				TriggerComp* interactiveTrigger = interactive->getComponent<DeskComp>();
				if (interactiveTrigger != nullptr) {
					SDL_FRect interactiveRect = interactiveTrigger->getRect();
					if (SDL_HasIntersectionF(&playerRect, &interactiveRect)) {
						interactiveTrigger->Overlap(player);
					}
					else {
						interactiveTrigger->Overlap(nullptr);
					}
				}
			}

			for (auto thiefs : *grp_Thiefs) {
				TriggerComp* thiefTrigger = thiefs->getComponent<TriggerComp>();
				if (thiefTrigger != nullptr) {
					SDL_FRect thiefsRect = thiefTrigger->getRect();
					if (SDL_HasIntersectionF(&playerRect, &thiefsRect)) {
						thiefTrigger->Overlap(player);
					}
					else {
						thiefTrigger->Overlap(nullptr);
					}
				}
			}
		}


	}


}

/*
bool CollisionsManager::hasCollision(GameObject* object) {
	bool c = false;
	CollisionComp* objCol = object->getComponent<CollisionComp>();
	SDL_FRect playerRect = objCol->getRect();
	int aux = 0;

	while (!c && aux < grup_Collisions->size()) {
		Transform* colT = (*grup_Collisions)[aux]->getComponent<Transform>();
		SDL_FRect colRect = { colT->getPos().getX(),colT->getPos().getY(),colT->getW(),colT->getW() };
		if (SDL_HasIntersectionF(&playerRect, &colRect)) {
			c = true;
		}
	}
	aux = 0;
	while (!c && aux < grp_Player->size()) {
		if (object != (*grp_Player)[aux])
		Transform* colT2 = (*grp_Player)[aux]->getComponent<Transform>();
		SDL_FRect colRect2 = { colT2->getPos().getX(),colTP->getPos().getY(),colTP->getW(),colTP->getW() };
		if (SDL_HasIntersectionF(&playerRect, &colRect2)) {
			c = true;

		}


	}

}*/