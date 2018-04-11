/*
 * FSMSupervisor.h
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#ifndef STATEMACHINE_FSMSUPERVISOR_H_
#define STATEMACHINE_FSMSUPERVISOR_H_

#include "AbstractState.h"

class FSMSupervisor {
public:
	FSMSupervisor();
	virtual ~FSMSupervisor();
	void setNextState(AbstractState* state);
	void update();

private:

	AbstractState* nextState;
	AbstractState* currentState;
};

extern FSMSupervisor fsmSupervisor;

#endif /* STATEMACHINE_FSMSUPERVISOR_H_ */
