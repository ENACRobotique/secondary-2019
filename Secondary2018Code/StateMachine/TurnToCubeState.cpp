 /*
* TurnToCubeState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "TurnToCubeState.h"
#include "LaunchBeeState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

TurnToCubeState turnToCubeState = TurnToCubeState();

TurnToCubeState::TurnToCubeState() {
	time_start = 0;
}

TurnToCubeState::~TurnToCubeState() {
	// TODO Auto-generated destructor stub
}

void TurnToCubeState::enter() {
	Serial.println("Etat rotation vers les cubes");
	navigator.turn_to(0,0);
	time_start = millis();
}

void TurnToCubeState::leave() {

}

void TurnToCubeState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&launchBeeState);
	}
}

void TurnToCubeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
}

void TurnToCubeState::forceLeave(){

}
