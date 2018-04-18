/*
 * RetractArmState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "RetractArmState.h"
#include "MoveToCubeState.h"
#include "TiretteState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

RetractArmState retractArmState = RetractArmState();

RetractArmState::RetractArmState() {
	time_start = 0;

}

RetractArmState::~RetractArmState() {
	// TODO Auto-generated destructor stub
}

void RetractArmState::enter() {
	Serial.println("Etat throw");
	time_start = millis();
	arm.write(0);
}

void RetractArmState::leave() {

}

void RetractArmState::doIt() {
	if (millis() - time_start > SERVO_MOVEMENT_DURATION) {
		fsmSupervisor.setNextState(&moveToCubeState);
	}

}

void RetractArmState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	arm.write(0);
}

void RetractArmState::forceLeave(){

}
