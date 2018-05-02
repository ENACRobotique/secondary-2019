/*
 * MoveToWaterState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToWaterState.h"
#include "TiretteState.h"
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
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
}

MoveToWaterState::~MoveToWaterState() {
	// TODO Auto-generated destructor stub
}

void MoveToWaterState::enter() {
	Serial.println("Etat déplacement vers l'eau");

	if(tiretteState.get_color() == GREEN){
		navigator.move_to(POS_X_WATER,POS_Y_WATER_GREEN);
	}
	else{
		navigator.move_to(POS_X_WATER,POS_Y_WATER_ORANGE);
	}

	if(navigator.moveForward()){
		Serial.println("Forward");
		usDistances.front_left = 0;
		usDistances.front_right = 0;
		usDistances.rear_left = 0;
		usDistances.rear_right = 0;
	}
	else{
		Serial.println("Backwards");
		usDistances.front_left = 0;
		usDistances.front_right = 0;
		usDistances.rear_left = 0;
		usDistances.rear_right = 0;
	}
	usManager.setMinRange(&usDistances);

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
	if(digitalRead(COLOR) == GREEN){
		navigator.move_to(POS_X_WATER,POS_Y_WATER_GREEN);
	}
	else{
		navigator.move_to(POS_X_WATER,POS_Y_WATER_ORANGE);
	}
}

void MoveToWaterState::forceLeave(){

}
