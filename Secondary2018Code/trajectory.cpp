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


float move_to(float x_cons,float y_cons)
{
	float speed_cons, dist_fore, t_stop, dist_objective;

	//Test de décélération (on suppose l'accélération minimale et on intègre deux fois)
	t_stop = Odometry::get_speed()/ACCEL_MAX;
	/*dist_fore = 2*(Odometry::get_speed()-1/2*ACCEL_MAX*pow(t_stop,2));*/
	dist_fore = Odometry::get_speed()*t_stop;

	dist_objective = sqrt(pow(x_cons - Odometry::get_pos_x(),2) + pow(y_cons - Odometry::get_pos_y(),2));

	//Si le point estimé est suffisamment proche du point voulu, on décélére, sinon on accélére jusqu'à la vitesse maximale.
	if(abs( dist_fore - dist_objective ) < ADMITTED_POSITION_ERROR){
		speed_cons = max(0,-ACCEL_MAX + Odometry::get_speed());
	}
	else{
		if(dist_fore - dist_objective > 0){
			speed_cons = max(0,Odometry::get_speed() - ACCEL_MAX);
		}
		else{
			speed_cons = min(SPEED_MAX,Odometry::get_speed() + ACCEL_MAX);
		}
	}
	if(dist_objective < ADMITTED_POSITION_ERROR){
		speed_cons = 0;
	}
	Serial.print("Distances estimées");
	Serial.print("\t");
	Serial.print(dist_fore - dist_objective);
	Serial.print("\t");
	Serial.print(dist_objective);
	Serial.print("\tspeed= ");
	Serial.println(Odometry::get_speed());
	return speed_cons;
}


float turn_to(float x_cons, float y_cons)
{
	float omega_cons, angle_fore, alpha,t_rotation_stop;
	int sgn;
	alpha = center_radian(atan2((-y_cons+Odometry::get_pos_y()),(-x_cons+Odometry::get_pos_x())) + PI);

	if (center_radian(alpha - Odometry::get_pos_theta()) > 0){
		sgn = 1;
	}
	else{
		sgn = -1;
	}
	t_rotation_stop = abs(Odometry::get_omega())/ACCEL_OMEGA_MAX;
	angle_fore = center_radian(Odometry::get_pos_theta() + 2.5*sgn*(abs(Odometry::get_omega())*t_rotation_stop -1/2*ACCEL_OMEGA_MAX*pow(t_rotation_stop,2)));
	if(abs(angle_fore - alpha) < ADMITTED_ANGLE_ERROR){
		omega_cons = sgn*max(0,abs(Odometry::get_omega()) - ACCEL_OMEGA_MAX);
	}
	else{
		if(abs(angle_fore) - abs(alpha) < 0){
			omega_cons = sgn*min(OMEGA_MAX, ACCEL_OMEGA_MAX + abs(Odometry::get_omega()));
		}
		else{
			omega_cons = sgn*max(0,abs(Odometry::get_omega()) - ACCEL_OMEGA_MAX);
		}
	}
	if(abs(Odometry::get_pos_theta() - alpha) < ADMITTED_ANGLE_ERROR){
		omega_cons = 0;
	}
	/*Serial.print("Consignes angles");
	Serial.print("\t");
	Serial.print(omega_cons);
	Serial.print("\t");
	Serial.print(angle_fore);
	Serial.print("\t");
	Serial.print(alpha);
	Serial.print("\t");
	Serial.println(Odometry::get_pos_theta());*/
	return omega_cons;
}


float center_radian(float angle)
{
	if (abs(angle) < PI){
		return angle;
	}
	if(angle<0){
		while(abs(angle)>PI){
			angle+=PI*2;
		}
		return angle;
	}
	else{
		while(abs(angle)>PI){
			angle-=2*PI;
		}
		return angle;
	}
}



