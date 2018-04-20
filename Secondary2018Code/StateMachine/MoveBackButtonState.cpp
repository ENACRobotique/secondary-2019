/*
 * MoveBackButtonState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "MoveBackButtonState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveBackButtonState moveBackButtonState = MoveBackButtonState();

MoveBackButtonState::MoveBackButtonState() {
	time_start = 0;
	flags = E_ULTRASOUND;
}

MoveBackButtonState::~MoveBackButtonState() {
	// TODO Auto-generated destructor stub
}

void MoveBackButtonState::enter() {
	Serial.println("Etat déplacement arrière depuis la zone de construction");
	navigator.move_to(400,0);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
}

void MoveBackButtonState::leave() {

}

void MoveBackButtonState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&throwState);
	}

}

void MoveBackButtonState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.move_to(400,0);
}

void MoveBackButtonState::forceLeave(){

}
