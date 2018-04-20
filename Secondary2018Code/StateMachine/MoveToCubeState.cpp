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
#include "../lib/USManager.h"

MoveToCubeState moveToCubeState = MoveToCubeState();

MoveToCubeState::MoveToCubeState() {
	time_start = 0;
	flags = E_ULTRASOUND;
}

MoveToCubeState::~MoveToCubeState() {
	// TODO Auto-generated destructor stub
}

void MoveToCubeState::enter() {
	Serial.println("Etat déplacement vers le cube");
	navigator.move_to(600,-200);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
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
	navigator.move_to(600,-200);
}

void MoveToCubeState::forceLeave(){

}
