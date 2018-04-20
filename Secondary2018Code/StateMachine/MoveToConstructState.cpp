/*
 * MoveToConstructState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "MoveToConstructState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveToConstructState moveToConstructState = MoveToConstructState();

MoveToConstructState::MoveToConstructState() {
	time_start = 0;
	flags = E_ULTRASOUND;
}

MoveToConstructState::~MoveToConstructState() {
	// TODO Auto-generated destructor stub
}

void MoveToConstructState::enter() {
	Serial.println("Etat déplacement vers la zone de construction");
	navigator.move_to(400,0);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
}

void MoveToConstructState::leave() {

}

void MoveToConstructState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&throwState);
	}

}

void MoveToConstructState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.move_to(400,0);
}

void MoveToConstructState::forceLeave(){

}
