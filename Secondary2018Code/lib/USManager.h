/*
 * USManager.h
 *
 *  Created on: 19 avr. 2018
 *      Author: robot
 */

#ifndef LIB_USMANAGER_H_
#define LIB_USMANAGER_H_
#include "Arduino.h"
#include "Ultrasound.h"
#include "../params.h"
class USManager {
public:
	USManager();
	virtual ~USManager();

	void init(uint8_t *tab_address);

	void setMinRange(uint16_t *tab_range);

	void update();

private:
	Ultrasound *tab_ultrasound[NB_US];
	int current_us;
};

#endif /* LIB_USMANAGER_H_ */
