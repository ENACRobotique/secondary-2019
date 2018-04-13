/*
 * behaviour.cpp
 *
 *  Created on: 10 avril 2018
 *      Author: Maxime
 */

#include "Secondary2018Code.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "math.h"
#include "trajectory.h"
#include "behaviour.h"

int turn(float x, float y)
{
	int i=0;
	float cons_omega = turn_to(x,y);
	MotorControl::set_cons(0,cons_omega);
	if ((Odometry::get_omega() < ADMITTED_OMEGA_ERROR) && (cons_omega == 0))
	{
		i=1;
	}

	return i;
}

void forward(float x, float y)
{
	float cons_speed = move_to(x,y);
	float cons_omega = turn_to(x,y);
	if(cons_speed ==0){
		cons_omega = 0;
	}
	/*Serial.print("Consignes forward");
	Serial.print("\t");
	Serial.print(cons_speed);
	Serial.print("\t");
	Serial.println(cons_omega);*/
	MotorControl::set_cons(cons_speed,cons_omega);
}
