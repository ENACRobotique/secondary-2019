/*
 * MoveToWaterState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToWaterState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

MoveToWaterState moveToWaterState = MoveToWaterState();

MoveToWaterState::MoveToWaterState() {
	time_start = 0;
}

MoveToWaterState::~MoveToWaterState() {
	// TODO Auto-generated destructor stub
}

void MoveToWaterState::enter() {
	Serial.println("Etat déplacement vers l'eau");
	navigator.move_to(400,0);
	time_start = millis();
}

void MoveToWaterState::leave() {

}

void MoveToWaterState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&throwState);
	}
}

void MoveToWaterState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
}

void MoveToWaterState::forceLeave(){

}
