/*
 * MoveToConstructState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "MoveToConstructState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveToConstructState moveToConstructState = MoveToConstructState();

MoveToConstructState::MoveToConstructState() {
	time_start = 0;
	flags = E_ULTRASOUND;
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
}

MoveToConstructState::~MoveToConstructState() {
	// TODO Auto-generated destructor stub
}

void MoveToConstructState::enter() {
	Serial.println("Etat déplacement vers la zone de construction");
	navigator.move_to(400,0);
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

void MoveToConstructState::leave() {

}

void MoveToConstructState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&throwState);
	}

}

void MoveToConstructState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.move_to(400,0);
}

void MoveToConstructState::forceLeave(){

}
