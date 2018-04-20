 /*
* TurnBeeLaunchState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "TurnBeeLaunchState.h"
#include "MoveToButtonState.h"
#include "RetractArmBeeState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "TiretteState.h"
#include "FSMSupervisor.h"

TurnBeeLaunchState turnBeeLaunchState = TurnBeeLaunchState();

TurnBeeLaunchState::TurnBeeLaunchState() {
	time_start = 0;
	time_servo=0;
}

TurnBeeLaunchState::~TurnBeeLaunchState() {
	// TODO Auto-generated destructor stub
}

void TurnBeeLaunchState::enter() {
	Serial.println("Etat rotation vers l'abeille");
	navigator.turn_to(-50);
	time_start = millis();
}

void TurnBeeLaunchState::leave() {

}

void TurnBeeLaunchState::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(time_servo == 0){
			time_servo = millis();
			arm.write(RETRACTED_ARM);
		}
		if(millis() - time_servo > SERVO_MOVEMENT_DURATION){
			fsmSupervisor.setNextState(&moveToButtonState);
		}
	}
}

void TurnBeeLaunchState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.turn_to(180);
}

void TurnBeeLaunchState::forceLeave(){

}
