/*
 * MoveToCubeState.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_MOVETOCUBESTATE_H_
#define STATEMACHINE_MOVETOCUBESTATE_H_

#include "AbstractState.h"

class MoveToCubeState : public AbstractState {
public:
	MoveToCubeState();
	virtual ~MoveToCubeState();

	void doIt();
	void leave();
	void enter();
	void reEnter(unsigned long interruptTime);
	void forceLeave();
	unsigned long get_time_start(){
		return time_start;
	}

private:

	unsigned long time_start;
};

extern MoveToCubeState moveToCubeState;

#endif /* STATEMACHINE_MOVETOCUBESTATE_H_ */
