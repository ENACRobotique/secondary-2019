/*
 * LaunchBeeState.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_LAUNCHBEESTATE_H_
#define STATEMACHINE_LAUNCHBEESTATE_H_

#include "AbstractState.h"

class LaunchBeeState : public AbstractState {
public:
	LaunchBeeState();
	virtual ~LaunchBeeState();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	unsigned long get_time_start(){
		return time_start;
	}

private:

	unsigned long time_start;
};

extern LaunchBeeState launchBeeState;

#endif /* STATEMACHINE_LAUNCHBEESTATE_H_ */
