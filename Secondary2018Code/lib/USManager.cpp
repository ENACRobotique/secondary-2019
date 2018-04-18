/*
 * USManager.cpp
 *
 *  Created on: 19 avr. 2018
 *      Author: robot
 */

#include "USManager.h"
#include "Ultrasound.h"

USManager::USManager() {
	// TODO Auto-generated constructor stub

}

USManager::~USManager() {
	// TODO Auto-generated destructor stub
}

void USManager::init(uint8_t* tab_address) {
	for(int i=0;i<NB_US;i++){
		tab_ultrasound[i] = new Ultrasound(tab_address[i]);
	}
}

void USManager::setMinRange(uint16_t* tab_range) {
	for(int i=0;i<NB_US;i++){
		tab_ultrasound[i]->setMinRange(tab_range[i]);
	}
}

void USManager::update() {
	unsigned long time_current_us = millis() - tab_ultrasound[current_us]->getRangeTime();
	tab_ultrasound[current_us]->update(false);
	if(time_current_us > 70){
		current_us = (current_us+1)%NB_US;
		tab_ultrasound[current_us]->update(true);
	}
}
