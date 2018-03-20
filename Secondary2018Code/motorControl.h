/*
 * motorControl.h
 *
 *  Created on: 20 mars 2018
 *      Author: elie
 */

#ifndef MOTORCONTROL_H_
#define MOTORCONTROL_H_

namespace MotorControl {
	void update();
	void init();

	void set_cons(float speed, float omega);
}


#endif /* MOTORCONTROL_H_ */
