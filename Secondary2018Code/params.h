/*
 * params.h
 *
 *  Created on: 18 mars 2018
 *      Author: elie
 */

#ifndef PARAMS_H_
#define PARAMS_H_
#include "Arduino.h"

const int ENCODEUR1_A = 21;
const int ENCODEUR1_B = 20;
const int ENCODEUR2_A = 17;
const int ENCODEUR2_B = 16;

const int MOT1_PWM = 6;
const int MOT1_DIR = 5;
const int MOT2_PWM = 28;
const int MOT2_DIR = 29;

const int SERVO1 = 39;
const int SERVO2 = 15;
const int SERVO3 = 37;

const int MOT_GALET_L = 35;
const int MOT_GALET_R = 36;

const int COLOR = 26;
const int TIRETTE = 25;

const int SPARE1 = 10;
const int SPARE2 = 9;
const int SPARE3 = 8;
const int SPARE4 = 7;

const int DYNAMIXEL_CONTROL = 30;

const float WHEEL_DIAMETER = 54.0;
const float WHEELBASE = 199.0;

const float INCR_TO_MM = PI*WHEEL_DIAMETER/800.0;

const float CONTROL_PERIOD = 0.05;

#endif /* PARAMS_H_ */
