/*
 * TiretteState.cpp
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#include "TiretteState.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"

TiretteState tiretteState = TiretteState();

TiretteState::TiretteState() {
	time_start = 0;

}

TiretteState::~TiretteState() {
	// TODO Auto-generated destructor stub
}

void TiretteState::enter() {
	Serial.println("Etat tirette");

}

void TiretteState::leave() {

}

void TiretteState::doIt() {
	if (digitalRead(TIRETTE)) {
		Serial.println("On change d'etat : gooooo!!");
		time_start = millis();
		fsmSupervisor.setNextState(&tiretteState); //TODO : définir un état au départ de la course
	}

}

void TiretteState::reEnter(unsigned long interruptTime){

}
