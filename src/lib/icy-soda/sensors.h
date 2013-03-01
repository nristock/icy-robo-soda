/*
 * sensors.h
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#define BTN_BACK 1
#define BTN_FRONT 2

void initSensors();
int readButton(uint8_t button);

#endif /* SENSORS_H_ */