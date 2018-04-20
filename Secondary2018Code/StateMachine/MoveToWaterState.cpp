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
#include "../lib/USManager.h"

MoveToWaterState moveToWaterState = MoveToWaterState();

MoveToWaterState::MoveToWaterState() {
	time_start = 0;
	flags = E_ULTRASOUND;
}

MoveToWaterState::~MoveToWaterState() {
	// TODO Auto-generated destructor stub
}

void MoveToWaterState::enter() {
	Serial.println("Etat déplacement vers l'eau");
	navigator.move_to(4000,0);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
}

void MoveToWaterState::leave() {

}

void MoveToWaterState::doIt() {
	if(navigator.isTrajectoryFinished()){
		fsmSupervisor.setNextState(&throwState);
	}

//	uint16_t* ranges = usManager.getRanges();
//	for(int i=0;i<NB_US;i++){
//		Serial.print(ranges[i]);
//		Serial.print("\t");
//	}
//	Serial.println("");
}

void MoveToWaterState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	Serial.println("I'm back");
	navigator.move_to(4000,0);
}

void MoveToWaterState::forceLeave(){
	Serial.println("I'll be back");
}
