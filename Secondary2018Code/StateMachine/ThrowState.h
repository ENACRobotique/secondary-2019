/*
 * ThrowState.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_THROWSTATE_H_
#define STATEMACHINE_THROWSTATE_H_

#include "AbstractState.h"

class ThrowState : public AbstractState {
public:
	ThrowState();
	virtual ~ThrowState();

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

extern ThrowState throwState;

#endif /* STATEMACHINE_THROWSTATE_H_ */
