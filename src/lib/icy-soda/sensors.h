/*
 * sensors.h
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#ifndef SENSORS_H_
#define SENSORS_H_

#include <stdint.h>
#include <stdbool.h>

#define BTN_BACK 1
#define BTN_FRONT 2

void initSensors();
bool readButton(uint8_t button);
unsigned char readLineSensor();

#endif /* SENSORS_H_ */
