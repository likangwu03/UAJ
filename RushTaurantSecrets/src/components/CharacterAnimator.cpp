#include "CharacterAnimator.h"

void CharacterAnimator::init() {
	plMov = parent->getComponent<PlayerMovementController>();
	parentOrientation = plTf->getOrientation();
	currOrientation = parentOrientation;
};


void CharacterAnimator::update() {
	//if (!plTf->isStatic()) {
	if (plTf->getMovState() == idle) currentAnim = 1;
	else if (plTf->getMovState() == walking) currentAnim = 2;
	else if (plTf->getMovState() == sitting) currentAnim = 4;
	//}

	parentOrientation = plTf->getOrientation();
	if (currOrientation != parentOrientation) {
		currOrientation = parentOrientation;
		if (currOrientation == east) {
			setCurrentAnim(0, 6, currentAnim);
		}
		else if (plTf->getOrientation() == north) {
			setCurrentAnim(6, 12, currentAnim);
		}
		else if (plTf->getOrientation() == west) {
			// las animaciones de sentado mirando hacia la izquierda están en otros frames
			if (currentAnim == 4) {
				setCurrentAnim(6, 12, currentAnim);
			}
			else {
				setCurrentAnim(12, 18, currentAnim);
			}
		}
		else if (plTf->getOrientation() == south) {
			setCurrentAnim(18, 24, currentAnim);
		}
	}

	Animator::update();
}
