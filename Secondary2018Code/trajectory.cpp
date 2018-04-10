/*
 * Trajectory.cpp
 *
 * Created on : 8 avril 2018
 * Author : Maxime
 */

#include "Secondary2018Code.h"
#include "params.h"
#include "odometry.h"
#include "motorControl.h"
#include "math.h"
#include "trajectory.h"


int move_to(int x_cons,int y_cons)
{
	float speed_cons, dist_fore;

	//Test de décélération (on suppose l'accélération minimale et on intègre deux fois)
	dist_fore = pow(Odometry::get_speed(),2)/(2*ACCEL_MAX);

	//Si le point estimé est suffisamment proche du point voulu, on décélére, sinon on accélére jusqu'à la vitesse maximale.
	if(abs( dist_fore - sqrt(pow(x_cons - Odometry::get_pos_x(),2) + pow(y_cons - Odometry::get_pos_y(),2) )) > ADMITTED_POSITION_ERROR){
		speed_cons = min(min(SPEED_MAX,MAX_DRIFT * Odometry::get_omega()),ACCEL_MAX + Odometry::get_speed());
	}
	else{
		speed_cons = max(0,Odometry::get_speed() - ACCEL_MAX);
	}

	return speed_cons;
}


int turn_to(int x_cons, int y_cons)
{
	float omega_cons, angle_fore, cap;
	int sgn;
	cap = atan2((y_cons-Odometry::get_pos_y()),(x_cons-Odometry::get_pos_x()));

	if (center_radian(cap - Odometry::get_pos_theta()) > 0){
		sgn = 1;
	}
	else{
		sgn = -1;
	}

	angle_fore = Odometry::get_pos_theta() + sgn*pow(Odometry::get_omega(),2)/(2*ACCEL_OMEGA_MAX);
	if(abs(angle_fore - cap) > ADMITTED_ANGLE_ERROR){
		omega_cons = sgn*min(OMEGA_MAX, ACCEL_MAX + abs(Odometry::get_omega()));
	}
	else{
		omega_cons = sgn*max(0,abs(Odometry::get_omega()) - ACCEL_OMEGA_MAX);
	}

	return omega_cons;
}


int center_radian(float angle)
{
	if (abs(angle) < 180){
		return angle;
	}
	if(angle<0){
		while(abs(angle)>180){
			angle+=360;
		}
		return angle;
	}
	else{
		while(abs(angle)>180){
			angle-=360;
		}
		return angle;
	}
}



