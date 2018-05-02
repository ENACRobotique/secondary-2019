/*
 * ThrowState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "ThrowState.h"
#include "MoveToBeeState.h"
#include "DeadState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "Servo.h"
#include "DynamixelSerial4.h"
#include "../Navigator.h"
#include "MoveToWaterState.h"

ThrowState throwState = ThrowState();

ThrowState::ThrowState() {
	time_start = 0;
	MOTOR_START_DURATION = 2000;
	VIBRATION_DURATION = 2000;
	dynamixel_not_started = true;
	time_last_vibration = 0;
	vibration_index = 0;
}

ThrowState::~ThrowState() {
	// TODO Auto-generated destructor stub
}

void ThrowState::enter() {
	Serial.println("Etat throw");
	time_start = millis();
	time_last_vibration = millis();
	analogWrite(MOT_GALET_L,13);
	analogWrite(MOT_GALET_R,13);
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

	if(millis() - time_last_vibration > VIBRATION_DURATION ){
			time_last_vibration = millis();
			float vibration[] = {POS_X_WATER -30, POS_X_WATER +10};
			if(digitalRead(COLOR) == GREEN){
				navigator.throw_to(vibration[vibration_index],POS_Y_WATER_GREEN);
			}
			else{
				navigator.throw_to(vibration[vibration_index],POS_Y_WATER_ORANGE);
			}
			vibration_index = (vibration_index+1)%2;
	}

}

void ThrowState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	analogWrite(MOT_GALET_L,13);
	analogWrite(MOT_GALET_R,13);
	dynamixel_not_started = true;
}

void ThrowState::forceLeave(){
	analogWrite(MOT_GALET_L,0);
	analogWrite(MOT_GALET_R,0);
	Dynamixel.turn(DYNAMIXEL_ID,false,0);
}
