/*
 * MovebackConstructState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "MoveBackConstructState.h"
#include "ThrowState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveBackConstructState moveBackConstructState = MoveBackConstructState();

MoveBackConstructState::MoveBackConstructState() {
	time_start = 0;
	flags = E_ULTRASOUND;
}

MoveBackConstructState::~MoveBackConstructState() {
	// TODO Auto-generated destructor stub
}

void MoveBackConstructState::enter() {
	Serial.println("Etat déplacement arrière depuis la zone de construction");
	navigator.move_to(400,0);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
}

void MoveBackConstructState::leave() {

}

void MoveBackConstructState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&throwState);
	}

}

void MoveBackConstructState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.move_to(400,0);
}

void MoveBackConstructState::forceLeave(){

}
