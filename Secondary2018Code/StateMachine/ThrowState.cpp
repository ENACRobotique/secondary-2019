/*
 * ThrowState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "ThrowState.h"
#include "MoveToBeeState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "Servo.h"

ThrowState throwState = ThrowState();

ThrowState::ThrowState() {
	time_start = 0;

}

ThrowState::~ThrowState() {
	// TODO Auto-generated destructor stub
}

void ThrowState::enter() {
	Serial.println("Etat throw");
	time_start = millis();
	//TODO Create a file to control the commands of the launcher
}

void ThrowState::leave() {

}

void ThrowState::doIt() {
	if (millis() - time_start > THROW_DURATION) {
		fsmSupervisor.setNextState(&moveToBeeState);
	}

}

void ThrowState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
}
