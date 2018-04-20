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
	MOTOR_START_DURATION = 2000;
	dynamixel_not_started = true;
}

ThrowState::~ThrowState() {
	// TODO Auto-generated destructor stub
}

void ThrowState::enter() {
	Serial.println("Etat throw");
	time_start = millis();
	analogWrite(MOT_GALET_L,12);
	analogWrite(MOT_GALET_R,12);
}

void ThrowState::leave() {
	analogWrite(MOT_GALET_L,0);
	analogWrite(MOT_GALET_R,0);
	Dynamixel.turn(DYNAMIXEL_ID,false,0);
}

void ThrowState::doIt() {
	if (millis() - time_start > THROW_DURATION) {
		fsmSupervisor.setNextState(&moveToBeeState);
	}

	if((millis() - time_start > MOTOR_START_DURATION)&& dynamixel_not_started){
		Dynamixel.setEndless(DYNAMIXEL_ID,true);
		Dynamixel.turn(DYNAMIXEL_ID,true,1023);
		dynamixel_not_started = false;
	}

}

void ThrowState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	analogWrite(MOT_GALET_L,12);
	analogWrite(MOT_GALET_R,12);
	dynamixel_not_started = true;
}

void ThrowState::forceLeave(){
	analogWrite(MOT_GALET_L,0);
	analogWrite(MOT_GALET_R,0);
	Dynamixel.turn(DYNAMIXEL_ID,false,0);
}
