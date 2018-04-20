/*
 * MoveLaunchButtonState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "MoveLaunchButtonState.h"
#include "RetractArmButtonState.h"
#include "TiretteState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveLaunchButtonState moveLaunchButtonState = MoveLaunchButtonState();

MoveLaunchButtonState::MoveLaunchButtonState() {
	time_start = 0;
	time_nav_start = 0;
}

MoveLaunchButtonState::~MoveLaunchButtonState() {
	// TODO Auto-generated destructor stub
}

void MoveLaunchButtonState::enter() {
	Serial.println("Etat activation du panneau");
	time_start = millis();
	arm.write(EXTENDED_ARM);
}

void MoveLaunchButtonState::leave() {

}

void MoveLaunchButtonState::doIt() {
	if(millis() - time_start > SERVO_MOVEMENT_DURATION){
		if(time_nav_start ==0){
			time_nav_start = millis();
			navigator.move_to(240,1875);
		}
		if(navigator.isTrajectoryFinished()){
			fsmSupervisor.setNextState(&retractArmButtonState);
		}
	}
}

void MoveLaunchButtonState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
}

void MoveLaunchButtonState::forceLeave(){

}
