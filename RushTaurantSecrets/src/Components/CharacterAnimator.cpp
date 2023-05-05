#include "CharacterAnimator.h"

#include "../Utilities/checkML.h"

void CharacterAnimator::init() {
	// inicialmente un personaje reproduce la animación idle hacia abajo
	// orientación anterior y actual
	parentOrientation = plTf->getOrientation();
	currOrientation = none;
	// mov anterior y actual
	parentMov = plTf->getMovState();
	currMov = noMov;
}


void CharacterAnimator::update() {
	bool movHaveChanged = false;
	// se guarda inicialmente la nueva orientación ya que
	// para sentarse se tienen que seleccionar filas distintas dependiendo de la dirección
	parentOrientation = plTf->getOrientation();

	// se comprueba si ha cambiado el estado de movimiento en el que se encontraba
	parentMov = plTf->getMovState();
	if (currMov != parentMov) {
		// se pone derecho el sprite en en el que se haya cogido otro frame
		angle = 0;

		// si ha cambiado, se selecciona el nuevo estado
		// y luego, se eligen los frames oportunos
		currMov = parentMov;
		movHaveChanged = true;

		if (currMov == idle) {
			animationParameters.currAnim = 1;
			hasOrientation = true;
		}
		else if (currMov == walking) {
			animationParameters.currAnim = 2;
			hasOrientation = true;
		}
		else if (currMov == sleeping) {
			animationParameters.currAnim = 3;
			setCurrentAnim(0, 6, animationParameters.currAnim);
			hasOrientation = false;
		}
		else if (currMov == pushing) {
			animationParameters.currAnim = 8;
			hasOrientation = true;
		}
		else if (currMov == sitting) {
			if (parentOrientation == west || parentOrientation == east) 
				animationParameters.currAnim = 4;

			else if (parentOrientation == north || parentOrientation == south)
				animationParameters.currAnim = 1;

			hasOrientation = true;
		}
		else if (currMov == phone) {
			animationParameters.currAnim = 6;
			setCurrentAnim(3, 9, animationParameters.currAnim);
			hasOrientation = false;
		}
		else if (currMov == dead) {
			animationParameters.currAnim = 19;
			// se cambia el ángulo para que se tumbe el sprite
			angle = 90;
			setCurrentAnim(3, 5, animationParameters.currAnim);
			hasOrientation = false;
		}
		else if (currMov == shooting) {
			animationParameters.currAnim = 17;
			hasOrientation = false;
		}
		else if (currMov == fallen) {
			animationParameters.currAnim = 0;
			angle = -90;
			setCurrentAnim(1, 1, animationParameters.currAnim);
			hasOrientation = false;
		}
	}

	if (hasOrientation) {
		// si no ha cambiado, se comprueba si la dirección ha cambiado
		// si es asi se cogen los frames oportunos
		if (currOrientation != parentOrientation || movHaveChanged) {

			currOrientation = parentOrientation;

			if (currOrientation == east) 
				// idle, corriendo, durmiendo, empujando, sentado y disparando
				setCurrentAnim(0, 6, animationParameters.currAnim);

			else if (currOrientation == north) 
				// idle, corriendo, empujando, sentado y disparando
				setCurrentAnim(6, 12, animationParameters.currAnim);
			
			else if (currOrientation == west) {
				// sentado
				if (currMov == sitting) 
					setCurrentAnim(6, 12, animationParameters.currAnim);
				
				// idle, corriendo, empujando y disparando
				else 
					setCurrentAnim(12, 18, animationParameters.currAnim);
				
			}
			else if (plTf->getOrientation() == south) 
				// idle, corriendo, empujando, sentado y disparando
				setCurrentAnim(18, 24, animationParameters.currAnim);
			
		}
	}

	Animator::update();
}