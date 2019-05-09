/*
 * TiretteState.h
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#ifndef STATEMACHINE_TIRETTESTATE_H_
#define STATEMACHINE_TIRETTESTATE_H_

#include "AbstractState.h"
#include "Servo.h"

class TiretteState : public AbstractState {
public:
	TiretteState();
	virtual ~TiretteState();

	int get_color();

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
	int COLOR_BEGIN;
};

extern TiretteState tiretteState;

extern Servo arm;

#endif /* STATEMACHINE_TIRETTESTATE_H_ */
