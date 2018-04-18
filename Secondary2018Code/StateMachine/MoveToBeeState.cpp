/*
 * MoveToBeeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToBeeState.h"
#include "TurnToBeeState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

MoveToBeeState moveToBeeState = MoveToBeeState();

MoveToBeeState::MoveToBeeState() {
	time_start = 0;
}

MoveToBeeState::~MoveToBeeState() {
	// TODO Auto-generated destructor stub
}

void MoveToBeeState::enter() {
	Serial.println("Etat déplacement vers l'abeille");
	navigator.move_to(400,0);
	time_start = millis();
}

void MoveToBeeState::leave() {

}

void MoveToBeeState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&turnToBeeState);
	}
	navigator.update();
}

void MoveToBeeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
}
