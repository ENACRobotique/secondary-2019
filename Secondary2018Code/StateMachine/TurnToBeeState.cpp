 /*
* TurnToBeeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "TurnToBeeState.h"
#include "TurnBeeLaunchState.h"
#include "TiretteState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

TurnToBeeState turnToBeeState = TurnToBeeState();

TurnToBeeState::TurnToBeeState() {
	time_start = 0;
	time_servo = 0;
}

TurnToBeeState::~TurnToBeeState() {
	// TODO Auto-generated destructor stub
}

void TurnToBeeState::enter() {
	Serial.println("Etat rotation vers l'abeille");
	navigator.turn_to(30);
	time_start = millis();
}

void TurnToBeeState::leave() {

}

void TurnToBeeState::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(time_servo == 0){
			time_servo = millis();
			arm.write(EXTENDED_ARM);
		}
		if(millis() - time_servo > SERVO_MOVEMENT_DURATION){
			fsmSupervisor.setNextState(&turnBeeLaunchState);
		}

	}
}

void TurnToBeeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.turn_to(180);
}

void TurnToBeeState::forceLeave(){

}
