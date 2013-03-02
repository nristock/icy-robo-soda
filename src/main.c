/*
 * main.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>
#include <util/delay.h>

#include <stdbool.h>

#define MAX_MOTOR_SPEED 100

#include "lib/i2c/i2cmaster.h"
#include "lib/icy-soda/motor.h"
#include "lib/icy-soda/sensors.h"
#include "lib/icy-soda/debug.h"

#include "steering.h"

#include "main.h"

int main() {
	hardwareInit();

	while (1) {
		handleTouchInterrupts();

		correctSteering();
	}
}

void handleTouchInterrupts() {
	if (readButton(BTN_FRONT)) {
		debugOut(DBG1, true);
	} else {
		debugOut(DBG1, false);
	}

	if (readButton(BTN_BACK)) {
		debugOut(DBG2, true);
	} else {
		debugOut(DBG2, false);
	}
}



void hardwareInit() {
	initMotors();
	initSensors();
	enableDebug();

	// signal HW READY state
	debugOut(DBG1, true);
	debugOut(DBG2, true);
	debugOut(DBG3, true);
	debugOut(DBG4, true);
	debugOut(DBG5, true);
	debugOut(DBG6, true);
	_delay_ms(1000);
	debugOut(DBG1, false);
	debugOut(DBG2, false);
	debugOut(DBG3, false);
	debugOut(DBG4, false);
	debugOut(DBG5, false);
	debugOut(DBG6, false);
}
