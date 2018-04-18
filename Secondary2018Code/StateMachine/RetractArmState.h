/*
 * RetractArmState.h
 *
 *  Created on: 18 avr. 2018
 *      Author: Maxime
 */

#ifndef STATEMACHINE_RETRACTARMSTATE_H_
#define STATEMACHINE_RETRACTARMSTATE_H_

#include "AbstractState.h"

class RetractArmState : public AbstractState {
public:
	RetractArmState();
	virtual ~RetractArmState();

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

extern RetractArmState retractArmState;

#endif /* STATEMACHINE_RETRACTARMSTATE_H_ */
