/*
 * LaunchBeeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "LaunchBeeState.h"
#include "RetractArmState.h"
#include "TiretteState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

LaunchBeeState launchBeeState = LaunchBeeState();

LaunchBeeState::LaunchBeeState() {
	time_start = 0;
}

LaunchBeeState::~LaunchBeeState() {
	// TODO Auto-generated destructor stub
}

void LaunchBeeState::enter() {
	Serial.println("Etat throw");
	time_start = millis();
	arm.write(90);
}

void LaunchBeeState::leave() {

}

void LaunchBeeState::doIt() {
	if (millis() - time_start > SERVO_MOVEMENT_DURATION) {
		fsmSupervisor.setNextState(&retractArmState);
	}

}

void LaunchBeeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	arm.write(90);
}

void LaunchBeeState::forceLeave(){

}
