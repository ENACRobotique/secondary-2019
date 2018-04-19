/*
 * MoveToCubeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToCubeState.h"
#include "DeadState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

MoveToCubeState moveToCubeState = MoveToCubeState();

MoveToCubeState::MoveToCubeState() {
	time_start = 0;
}

MoveToCubeState::~MoveToCubeState() {
	// TODO Auto-generated destructor stub
}

void MoveToCubeState::enter() {
	Serial.println("Etat déplacement vers le cube");
	navigator.move_to(400,0);
	time_start = millis();
}

void MoveToCubeState::leave() {

}

void MoveToCubeState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&deadState);
	}
}

void MoveToCubeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
}

void MoveToCubeState::forceLeave(){

}
