/*
 * odometry.cpp
 *
 *  Created on: 19 mars 2018
 *      Author: elie
 */
#include "odometry.h"
#include "Arduino.h"
#include "params.h"

namespace Odometry{

	volatile int _incr1;
	volatile int _incr2;

	float pos_x, pos_y, pos_theta;

	void init(){
		pinMode(ENCODEUR1_A,INPUT_PULLUP);
		pinMode(ENCODEUR1_B,INPUT_PULLUP);
		attachInterrupt(ENCODEUR1_A, isr1, FALLING);
		_incr1 = 0;

		pinMode(ENCODEUR2_A,INPUT_PULLUP);
		pinMode(ENCODEUR2_B,INPUT_PULLUP);
		attachInterrupt(ENCODEUR2_A, isr2, RISING);
		_incr2 = 0;

		pos_x = pos_y = pos_theta = 0;


	}

	void isr1() {
		if(digitalRead(ENCODEUR1_B)) {
			_incr1++;
		}
		else {
			_incr1--;
		}
	}

	void isr2() {
			if(digitalRead(ENCODEUR2_B)) {
				_incr2++;
			}
			else {
				_incr2--;
			}
		}

	void update() {
		cli();
		int incr1 = _incr1;
		int incr2 = _incr2;
		_incr1 = _incr2 = 0;
		sei();

		float length = ((float)(incr1+incr2)/2.0)*INCR_TO_MM;
		float angle = ((float)(incr2-incr1)*INCR_TO_MM)/WHEELBASE;

		//TODO : vérifier formule
		pos_x = pos_x + length*cos(pos_theta + angle/2.0);
		pos_y = pos_y + length*sin(pos_theta + angle/2.0);
		pos_theta = pos_theta + angle;


		Serial.print(pos_x);
		Serial.print("\t");
		Serial.print(pos_y);
		Serial.print("\t");
		Serial.println(pos_theta);
	}
}






