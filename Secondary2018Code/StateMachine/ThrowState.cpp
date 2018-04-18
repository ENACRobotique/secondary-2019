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
#include "DynamixelSerial4.h"

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
	analogWrite(MOT_GALET_L,42);
	analogWrite(MOT_GALET_L,42);
	Dynamixel.setEndless(DYNAMIXEL_ID,true);
	Dynamixel.turn(DYNAMIXEL_ID,false,1023);
}

void ThrowState::leave() {
	analogWrite(MOT_GALET_L,0);
	analogWrite(MOT_GALET_L,0);
	Dynamixel.turn(DYNAMIXEL_ID,false,0);
}

void ThrowState::doIt() {
	if (millis() - time_start > THROW_DURATION) {
		fsmSupervisor.setNextState(&moveToBeeState);
	}

}

void ThrowState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	analogWrite(MOT_GALET_L,42);
	analogWrite(MOT_GALET_L,42);
	Dynamixel.setEndless(DYNAMIXEL_ID,true);
	Dynamixel.turn(DYNAMIXEL_ID,false,1023);
}

void ThrowState::forceLeave(){
	analogWrite(MOT_GALET_L,0);
	analogWrite(MOT_GALET_L,0);
	Dynamixel.turn(DYNAMIXEL_ID,false,0);
}
