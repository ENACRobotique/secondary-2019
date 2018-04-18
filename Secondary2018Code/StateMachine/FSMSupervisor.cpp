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
#include "../params.h"

FSMSupervisor fsmSupervisor = FSMSupervisor();

FSMSupervisor::FSMSupervisor() {
	// TODO Auto-generated constructor stub
	nextState = NULL;
	currentState = NULL;
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

	if(nextState != NULL){
		currentState->leave();
		nextState->enter();
		currentState = nextState;
	}
	currentState->doIt();
}
