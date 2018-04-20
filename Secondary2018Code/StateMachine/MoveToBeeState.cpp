/*
 * MoveToBeeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToBeeState.h"
#include "TurnToBeeState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveToBeeState moveToBeeState = MoveToBeeState();

float traj[][2] = {	{990, 2830},
					{990, 2200},
					{1550,2200},
					{1550,2830},
					{1800,2830}
};

MoveToBeeState::MoveToBeeState() {
	time_start = 0;
	flags = E_ULTRASOUND;
	trajectory_index = 0;
}

MoveToBeeState::~MoveToBeeState() {
	// TODO Auto-generated destructor stub
}

void MoveToBeeState::enter() {
	Serial.println("Etat déplacement vers l'abeille");
	navigator.move_to(traj[0][0],traj[0][1]);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
}

void MoveToBeeState::leave() {

}

void MoveToBeeState::doIt() {
	if(navigator.isTrajectoryFinished()){
		if(trajectory_index == 5){
			fsmSupervisor.setNextState(&turnToBeeState);
		}
		else{
			trajectory_index+=1;
			navigator.move_to(traj[trajectory_index][0],traj[trajectory_index][1]);
		}
	}

}

void MoveToBeeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.move_to(1000,0);
}

void MoveToBeeState::forceLeave(){

}
