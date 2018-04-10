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
	Serial.print("test");
	int i=0;
	MotorControl::set_cons(0,turn_to(x,y));
	Serial.println(MotorControl::get_cons_omega());
	if (MotorControl::get_cons_omega() == 0)
	{
		i=1;
	}

	return i;
}

void forward(float x, float y)
{
	MotorControl::set_cons(move_to(x,y),turn_to(x,y));
}
