/*
 * TurnBeeLaunchState.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_TURNBEELAUNCHSTATE_H_
#define STATEMACHINE_TurnBEELAUNCHSTATE_H_

#include "AbstractState.h"

class TurnBeeLaunchState : public AbstractState {
public:
	TurnBeeLaunchState();
	virtual ~TurnBeeLaunchState();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	void forceLeave();
	unsigned long get_time_start(){
		return time_start;
	}

private:
	unsigned long time_servo;
	unsigned long time_start;
};

extern TurnBeeLaunchState turnBeeLaunchState;

#endif /* STATEMACHINE_TURNBEELAUNCHSTATE_H_ */
