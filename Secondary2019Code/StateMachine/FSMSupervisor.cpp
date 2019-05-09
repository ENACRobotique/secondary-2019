/*
 * FSMSupervisor.cpp
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#include "FSMSupervisor.h"
#include "Arduino.h"
#include "AbstractState.h"
#include "TiretteState.h"
#include "DeadState.h"
#include "PauseState.h"
#include "../params.h"
#include "../lib/USManager.h"

FSMSupervisor fsmSupervisor = FSMSupervisor();

FSMSupervisor::FSMSupervisor() {
	// TODO Auto-generated constructor stub
	nextState = NULL;
	currentState = NULL;
	previousState = NULL;
	time_obstacle_left = 0;
}

FSMSupervisor::~FSMSupervisor() {
	// TODO Auto-generated destructor stub
}

void FSMSupervisor::setNextState(AbstractState* state) {
	nextState = state;
}

void FSMSupervisor::update() {
	if (millis() - tiretteState.get_time_start() > TIME_RACE){
		fsmSupervisor.setNextState(&deadState); //TODO Créer un état où le robot s'arrête
	}

	if(nextState != NULL && nextState != currentState){
		currentState->leave();
		nextState->enter();
		currentState = nextState;
		nextState = NULL;
	}

	currentState->doIt();

	/*if(currentState->getFlags() & E_ULTRASOUND){
		usManager.update();
		if(usManager.obstacleDetected()){
			time_obstacle_left = 0;
			if(currentState != &pauseState){			// on va dans l'état pause
				currentState->forceLeave();
				previousState = currentState;
				currentState = &pauseState;
				pauseState.enter();
			}

		}
		else {
			if(currentState == &pauseState && previousState != NULL){		// on revient dans l'état précédent !
				if(time_obstacle_left == 0){
					time_obstacle_left = millis();
				}
				if(millis() - time_obstacle_left > DETECTION_STOP_TIME){ //Permet de ne pas repartir directement quand on ne détecte plus d'adversaires
					pauseState.leave();
					previousState->reEnter(pauseState.getPauseTime());
					currentState = previousState;
					previousState = &pauseState;
					time_obstacle_left = 0; //May be useless (just like the primary)
				}
			}
		}
	}*/

}

void FSMSupervisor::init(AbstractState* state) {
	currentState = state;
	Serial.println("INIT FMS");
	state->enter();
}
