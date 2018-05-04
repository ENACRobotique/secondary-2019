/*
 * MoveToCubeState.cpp
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#include "MoveToCubeState.h"
#include "MoveToButtonState.h"
#include "DeadState.h"
#include "TiretteState.h"
#include "../Navigator.h"
#include "Arduino.h"
#include "../params.h"
#include "FSMSupervisor.h"
#include "../lib/USManager.h"

MoveToCubeState moveToCubeState = MoveToCubeState();

float traj_cube_green[][2] = { 	{1550,200},
								{1550,850},
								{200,850}
};

float traj_cube_orange[][2] = {	{1550, 2800},
								{1550,2150},
								{200,2150},
};

MoveToCubeState::MoveToCubeState() {
	time_start = 0;
	trajectory_index = 0;
	flags = E_ULTRASOUND;
	usDistances.front_left = 0;
	usDistances.front_right = 0;
	usDistances.rear_left = 0;
	usDistances.rear_right = 0;
}

MoveToCubeState::~MoveToCubeState() {
	// TODO Auto-generated destructor stub
}

void MoveToCubeState::enter() {
	Serial.println("Etat déplacement vers l'abeille");

	if(tiretteState.get_color() == GREEN){
		navigator.move_to(traj_cube_green[0][0],traj_cube_green[0][1]);
	}
	else{
		navigator.move_to(traj_cube_orange[0][0],traj_cube_orange[0][1]);
	}

	if(navigator.moveForward()){
		Serial.println("Forward");
		usDistances.front_left = 30;
		usDistances.front_right = 30;
		usDistances.rear_left = 0;
		usDistances.rear_right = 0;
	}
	else{
		Serial.println("Backwards");
		usDistances.front_left = 0;
		usDistances.front_right = 0;
		usDistances.rear_left = 30;
		usDistances.rear_right = 30;
	}
	usManager.setMinRange(&usDistances);

	time_start = millis();
}
void MoveToCubeState::leave() {

}

void MoveToCubeState::doIt() {
	if(navigator.isTrajectoryFinished()){
		Serial.print("trajectory:");
		Serial.println(trajectory_index);
		if(trajectory_index == 2){
			fsmSupervisor.setNextState(&moveToButtonState);
		}
		else{
			trajectory_index+=1;

			if(tiretteState.get_color() == GREEN){
				navigator.move_to(traj_cube_green[trajectory_index][0],traj_cube_green[trajectory_index][1]);
			}
			else{
				Serial.println("Orange");
				navigator.move_to(traj_cube_orange[trajectory_index][0],traj_cube_orange[trajectory_index][1]);
			}

			if(navigator.moveForward()){
				Serial.println("Forward");
				if(trajectory_index==2){
					usDistances.front_left = 0;
					usDistances.front_right = 0;
					usDistances.rear_left = 0;
					usDistances.rear_right = 0;
				}
				else{
					usDistances.front_left = 30;
					usDistances.front_right = 30;
					usDistances.rear_left = 0;
					usDistances.rear_right = 0;
				}
			}
			else{

				Serial.println("Backwards");
				if(trajectory_index==2){
					usDistances.front_left = 0;
					usDistances.front_right = 0;
					usDistances.rear_left = 0;
					usDistances.rear_right = 0;
				}
				else{
					usDistances.front_left = 0;
					usDistances.front_right = 0;
					usDistances.rear_left = 30;
					usDistances.rear_right = 30;
				}
			}
			usManager.setMinRange(&usDistances);
		}
	}

}

void MoveToCubeState::reEnter(unsigned long interruptTime){
	time_start+=interruptTime;
	if(tiretteState.get_color() == GREEN){
		navigator.move_to(traj_cube_green[trajectory_index][0],traj_cube_green[trajectory_index][1]);
	}
	else{
		navigator.move_to(traj_cube_orange[trajectory_index][0],traj_cube_orange[trajectory_index][1]);
	}
}

void MoveToCubeState::forceLeave(){

}
