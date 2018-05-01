/*
 * MoveToCubeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToCubeState.h"
#include "DeadState.h"
#include "TiretteState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveToCubeState moveToCubeState = MoveToCubeState();

MoveToCubeState::MoveToCubeState() {
	time_start = 0;
	flags = E_ULTRASOUND;
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
}

MoveToCubeState::~MoveToCubeState() {
	// TODO Auto-generated destructor stub
}

void MoveToCubeState::enter() {
	Serial.println("Etat déplacement vers le cube");

	if(tiretteState.get_color() == GREEN){

	}
	else{
		navigator.move_to(400,0);
	}

	if(navigator.moveForward()){
		Serial.println("Forward");
		usDistances.front_left = 30;
		usDistances.front_right = 30;
		usDistances.rear_left = 0;
		usDistances.rear_right = 0;
	}
	else{
		Serial.println("Backwards");
		usDistances.front_left = 0;
		usDistances.front_right = 0;
		usDistances.rear_left = 30;
		usDistances.rear_right = 30;
	}
	usManager.setMinRange(&usDistances);

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
	navigator.move_to(400,0);
}

void MoveToCubeState::forceLeave(){

}
