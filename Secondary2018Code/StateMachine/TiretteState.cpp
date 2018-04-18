/*
 * TiretteState.cpp
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#include "TiretteState.h"
#include "MoveToWaterState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "DynamixelSerial4.h"

TiretteState tiretteState = TiretteState();
Servo arm = Servo();

TiretteState::TiretteState() {
	time_start = 0;

}

TiretteState::~TiretteState() {
	// TODO Auto-generated destructor stub
}

void TiretteState::enter() {
	Serial.println("Etat tirette");
	Dynamixel.begin(1000000, DYNAMIXEL_CONTROL);
	arm.attach(SERVO1);
}

void TiretteState::leave() {

}

void TiretteState::doIt() {
	if (digitalRead(TIRETTE)) {
		Serial.println("On change d'etat : gooooo!!");
		time_start = millis();
		fsmSupervisor.setNextState(&moveToWaterState);
	}

}

void TiretteState::reEnter(unsigned long interruptTime){

}

void TiretteState::forceLeave(){

}
