/*
 * MoveToButtonState.cpp
 *
 *  Created on: 20 avr. 2018
 *      Author: Maxime
 */

#include "MoveToButtonState.h"
#include "MoveLaunchButtonState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveToButtonState moveToButtonState = MoveToButtonState();

float traj_to_button[][2] = {	{830,1875},
					{350,1875}
};

MoveToButtonState::MoveToButtonState() {
	time_start = 0;
	trajectory_index = 0;
	time_servo = 0;
	flags = E_ULTRASOUND;
}

MoveToButtonState::~MoveToButtonState() {
	// TODO Auto-generated destructor stub
}

void MoveToButtonState::enter() {
	Serial.println("Etat déplacement vers le bouton");
	navigator.move_to(traj_to_button[0][0],traj_to_button[0][1]);
	time_start = millis();
	uint16_t USmin_ranges[] = {30, 30, 30, 30} ;
	usManager.setMinRange(USmin_ranges);
}

void MoveToButtonState::leave() {

}

void MoveToButtonState::doIt() {
	if(navigator.isTrajectoryFinished()){
			if(trajectory_index == 1){
				fsmSupervisor.setNextState(&moveLaunchButtonState);
			}
			else{
				trajectory_index+=1;
				navigator.move_to(traj_to_button[trajectory_index][0],traj_to_button[trajectory_index][1]);
			}
		}
}

void MoveToButtonState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	navigator.move_to(400,0);
}

void MoveToButtonState::forceLeave(){

}
