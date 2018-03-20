/*
 * motorControl.cpp
 *
 *  Created on: 20 mars 2018
 *      Author: elie
 */


#include "odometry.h"
#include "Arduino.h"
#include "params.h"
#include "motorControl.h"

int clamp(int inf, int sup, float x) {
	return min(sup, max(inf, x));
}

int direction_sign(int nb) {
	if(nb>0) {
		return 0;
	}
	else {
		return 1;
	}
}

namespace MotorControl {

	float cons_speed;
	float cons_omega;
	float Ki_speed = 0;
	float Kp_speed = 1;
	float Kd_speed = 0;
	float Ki_omega = 0;
	float Kp_omega = 1;
	float Kd_omega = 0;

	float error_integrale_speed;
	float error_integrale_omega;

	void set_cons(float speed, float omega) {
		cons_speed = speed;
		cons_omega = omega;
	}



	void init() {
		pinMode(MOT1_DIR, OUTPUT);
		pinMode(MOT1_PWM, OUTPUT);
		pinMode(MOT2_DIR, OUTPUT);
		pinMode(MOT2_PWM, OUTPUT);
		cons_omega = cons_speed = 0;
		error_integrale_omega = error_integrale_speed = 0;


	}

	void update() {

		float error_speed = cons_speed - Odometry::get_speed();
		error_integrale_speed += error_speed;
		float cmd_speed = Kp_speed * error_speed + Ki_speed * error_integrale_speed;

		float error_omega = cons_omega - Odometry::get_omega();
		error_integrale_omega += error_omega;
		float cmd_omega = Kp_omega * error_omega + Ki_omega * error_integrale_omega;

		int cmd_mot1 = clamp(-255, 255, cmd_speed - cmd_omega);
		int cmd_mot2 = -clamp(-255, 255, cmd_speed + cmd_omega);

		analogWrite(MOT1_PWM, abs(cmd_mot1));
		digitalWrite(MOT1_DIR, direction_sign(cmd_mot1));
		analogWrite(MOT2_PWM, abs(cmd_mot2));
		digitalWrite(MOT2_DIR, direction_sign(cmd_mot2));

		Serial.print(error_speed);
		Serial.print("\t");
		Serial.print(error_omega);
		Serial.print("\t");
		Serial.print(cmd_mot1);
		Serial.print("\t");
		Serial.println(cmd_mot2);
	}
}
