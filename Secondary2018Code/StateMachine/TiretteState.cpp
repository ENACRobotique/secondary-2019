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
//#include "WireKinetis.h"
#include "../libraries/i2c_t3/i2c_t3.h"
#include "../lib/USManager.h"

TiretteState tiretteState = TiretteState();
Servo arm = Servo();

TiretteState::TiretteState() {
	time_start = 0;
	flags = E_ULTRASOUND;
}

TiretteState::~TiretteState() {
	// TODO Auto-generated destructor stub
}

void TiretteState::enter() {
	time_start = millis();
	Serial.println("Etat tirette");
	Dynamixel.begin(1000000, DYNAMIXEL_CONTROL);
	arm.attach(SERVO3);
	pinMode(TIRETTE,INPUT_PULLUP);
	pinMode(COLOR,INPUT_PULLUP);
	//Wire2.begin();
    Wire2.begin(I2C_MASTER, 0x00, I2C_PINS_3_4, I2C_PULLUP_EXT, 400000);
	Wire2.setSDA(4);
	Wire2.setSCL(3);
	//Wire2.setSDA(4);
	//Wire2.setSCL(3);
	uint8_t USadresses[] = {0X71, 0X75, 0X73, 0X70};
	usManager.init(USadresses);
}

void TiretteState::leave() {

}

void TiretteState::doIt() {
	time_start = millis();
	if (!digitalRead(TIRETTE)) {
		Serial.println("On change d'etat : gooooo!!");
		time_start = millis();
		fsmSupervisor.setNextState(&moveToWaterState);
	}
	uint16_t* ranges = usManager.getRanges();
	for(int i=0;i<NB_US;i++){
		Serial.print(ranges[i]);
		Serial.print("\t");
	}
	Serial.println("");
}

void TiretteState::reEnter(unsigned long interruptTime){

}

void TiretteState::forceLeave(){

}
