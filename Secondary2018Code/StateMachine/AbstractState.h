/*
 * AbstractState.h
 *
 *  Created on: 11 avr. 2018
 *      Author: robot
 */

#ifndef STATEMACHINE_ABSTRACTSTATE_H_
#define STATEMACHINE_ABSTRACTSTATE_H_

class AbstractState {
public:
	AbstractState();
	virtual ~AbstractState() {};

	virtual void enter() = 0;
	virtual void doIt() = 0;
	virtual void leave() = 0;
	virtual void reEnter(unsigned long InterruptTime) = 0;
};

#endif /* STATEMACHINE_ABSTRACTSTATE_H_ */
