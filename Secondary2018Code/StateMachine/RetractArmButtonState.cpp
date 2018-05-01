/*
 * RetractArmButtonState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "RetractArmButtonState.h"
#include "DeadState.h"
#include "MoveToCubeState.h"
#include "TiretteState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../Navigator.h"

RetractArmButtonState retractArmButtonState = RetractArmButtonState();

RetractArmButtonState::RetractArmButtonState() {
	time_start = 0;
	time_servo = 0;
}

RetractArmButtonState::~RetractArmButtonState() {
	// TODO Auto-generated destructor stub
}

void RetractArmButtonState::enter() {
	Serial.println("Etat rangement du bras");
	time_start = millis();
	navigator.move_to(350,1875);
	arm.write(RETRACTED_ARM);
}

void RetractArmButtonState::leave() {

}

void RetractArmButtonState::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(time_servo ==0){
			time_servo = millis();
		}
		if (millis() - time_servo > SERVO_MOVEMENT_DURATION) {
			fsmSupervisor.setNextState(&deadState);
		}
	}

}

void RetractArmButtonState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	arm.write(170);
}

void RetractArmButtonState::forceLeave(){

}
