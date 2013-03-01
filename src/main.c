/*
 * main.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>
#include <util/delay.h>

#include "lib/i2c/i2cmaster.h"
#include "lib/icy-soda/motor.h"
#include "lib/icy-soda/sensors.h"
#include "lib/icy-soda/debug.h"

int main() {

	initMotors();
	initSensors();
	enableDebug();

	debugOut(DBG6, true);

	while (1) {

	}
}

