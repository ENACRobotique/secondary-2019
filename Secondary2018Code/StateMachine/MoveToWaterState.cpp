/*
 * MoveToWaterState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToWaterState.h"
#include "TiretteState.h"
#include "ThrowState.h"
#include "DeadState.h"
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

	if(tiretteState.get_color() == GREEN){
		navigator.move_to(POS_X_WATER,POS_Y_WATER_GREEN);
		Serial.print("color1");
	}
	else{
		navigator.move_to(POS_X_WATER,POS_Y_WATER_ORANGE);
		Serial.print("color2");
	}
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

}

void MoveToWaterState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	if(digitalRead(COLOR) == GREEN){
		navigator.move_to(POS_X_WATER,POS_Y_WATER_GREEN);
	}
	else{
		navigator.move_to(POS_X_WATER,POS_Y_WATER_ORANGE);
	}
}

void MoveToWaterState::forceLeave(){

}
