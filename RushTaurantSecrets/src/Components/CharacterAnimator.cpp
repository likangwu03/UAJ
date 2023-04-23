#include "CharacterAnimator.h"

#include "../Utilities/checkML.h"

void CharacterAnimator::init() {
	// inicialmente un personaje reproduce la animaci�n idle hacia abajo
	// orientaci�n anterior y actual
	parentOrientation = plTf->getOrientation();
	currOrientation = none;
	// mov anterior y actual
	parentMov = plTf->getMovState();
	currMov = noMov;
};


void CharacterAnimator::update() {
	//if (!plTf->isStatic()) {

	bool movHaveChanged = false;
	// se guarda inicialmente la nueva orientaci�n ya que
	// para sentarse se tienen que seleccionar filas distintas dependiendo de la direcci�n
	parentOrientation = plTf->getOrientation();

	// se comprueba si ha cambiado el estado de movimiento en el que se encontraba
	parentMov = plTf->getMovState();
	if (currMov != parentMov) {
		// se pone derecho el sprite en el caso de que se haya otro sprite
		angle = 0;

		// si ha cambiado, se selecciona el nuevo estado
		// y luego, se eligen los frames oportunos
		currMov = parentMov;
		movHaveChanged = true;

		if (currMov == idle) {
			animationParameters.currAnim = 1;
		}
		else if (currMov == walking) {
			animationParameters.currAnim = 2;
		}
		else if (currMov == sitting) {
			if (parentOrientation == west || parentOrientation == east) {
				animationParameters.currAnim = 4;
			}
			else if (parentOrientation == north || parentOrientation == south) {
				animationParameters.currAnim = 1;
			}
		}
		else if (currMov == dead) {
			animationParameters.currAnim = 19;
			// se cambia el �ngulo para que se tumbe el sprite
			angle = 90;
		}
	}

	// si no ha cambiado, se comprueba si la direcci�n ha cambiado
	// si es as? se cogen los frames oportunos
	if (currOrientation != parentOrientation || movHaveChanged) {

		currOrientation = parentOrientation;

		if (currOrientation == east) {
			// muerto
			if (animationParameters.currAnim == 19) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// idle, corriendo y sentado
			else {
				setCurrentAnim(0, 6, animationParameters.currAnim);
			}
		}
		else if (currOrientation == north) {
			// muerto
			if (animationParameters.currAnim == 19) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// idle, corriendo y sentado
			else {
				setCurrentAnim(6, 12, animationParameters.currAnim);
			}
		}
		else if (currOrientation == west) {
			// sentado
			if (animationParameters.currAnim == 4) {
				setCurrentAnim(6, 12, animationParameters.currAnim);
			}
			// muerto
			else if (animationParameters.currAnim == 19) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// idle y corriendo
			else {
				setCurrentAnim(12, 18, animationParameters.currAnim);
			}
		}
		else if (plTf->getOrientation() == south) {
			// muerto
			if (animationParameters.currAnim == 19) {
				setCurrentAnim(3, 5, animationParameters.currAnim);
			}
			// idle, corriendo y sentado
			else {
				setCurrentAnim(18, 24, animationParameters.currAnim);
			}
		}
	}
	Animator::update();
}