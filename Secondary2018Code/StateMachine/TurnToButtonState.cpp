 /*
* TurnToButtonState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "TurnToButtonState.h"
#include "DeadState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

TurnToButtonState turnToButtonState = TurnToButtonState();

TurnToButtonState::TurnToButtonState() {
	time_start = 0;
}

TurnToButtonState::~TurnToButtonState() {
	// TODO Auto-generated destructor stub
}

void TurnToButtonState::enter() {
	Serial.println("Etat rotation vers l'abeille");
	navigator.turn_to(180);
	time_start = millis();
}

void TurnToButtonState::leave() {

}

void TurnToButtonState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&deadState);
	}
}

void TurnToButtonState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.turn_to(180);
}

void TurnToButtonState::forceLeave(){

}
