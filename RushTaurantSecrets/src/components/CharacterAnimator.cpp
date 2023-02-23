#include "CharacterAnimator.h"

#include "../utils/checkML.h"

void CharacterAnimator::init() {
	// inicialmente un personaje reproduce la animación idle hacia abajo
	// orientación anterior y actual
	parentOrientation = plTf->getOrientation();
	currOrientation = none;
	// mov anterior y actual
	parentMov = plTf->getMovState();
	currMov = noMov;
};


void CharacterAnimator::update() {
	//if (!plTf->isStatic()) {

	bool movHaveChanged = false;
	// se guarda inicialmente la nueva orientación ya que
	// para sentarse se tienen que seleccionar filas distintas dependiendo de la dirección
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
			currentAnim = 1;
		}
		else if (currMov == walking) {
			currentAnim = 2;
		}
		else if (currMov == sitting) {
			if (parentOrientation == west || parentOrientation == east) {
				currentAnim = 4;
			}
			else if (parentOrientation == north || parentOrientation == south) {
				currentAnim = 1;
			}
		}
		else if (currMov == dead) {
			currentAnim = 19;
			angle = 90;
		}
	}
	//}

	// si no ha cambiado, se comprueba si la dirección ha cambiado
	// si es así, se cogen los frames oportunos
	if (currOrientation != parentOrientation || movHaveChanged) {
		
		currOrientation = parentOrientation;

		if (currOrientation == east) {
			setCurrentAnim(0, 6, currentAnim);
		}
		else if (currOrientation == north) {
			setCurrentAnim(6, 12, currentAnim);
		}
		else if (currOrientation == west) {
			// sentado
			if (currentAnim == 4) {
				setCurrentAnim(6, 12, currentAnim);
			}
			// muerto
			else if (currentAnim == 19) {
				// se cambia el ángulo para que se tumbe el sprite
				setCurrentAnim(7, 7, currentAnim);
			}
			// corriendo y idle
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
