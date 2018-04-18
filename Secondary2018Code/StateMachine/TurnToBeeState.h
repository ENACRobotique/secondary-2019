/*
 * TurnToBeeState.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_TURNTOBEESTATE_H_
#define STATEMACHINE_TURNTOBEESTATE_H_

#include "AbstractState.h"

class TurnToBeeState : public AbstractState {
public:
	TurnToBeeState();
	virtual ~TurnToBeeState();

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

extern TurnToBeeState turnToBeeState;

#endif /* STATEMACHINE_TURNTOBEESTATE_H_ */
