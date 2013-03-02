/*
 * steering.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>
#include <util/delay.h>

#include "lib/icy-soda/sensors.h"
#include "lib/icy-soda/motor.h"
#include "lib/icy-soda/debug.h"

void dbg(unsigned char laRaw) {
	debugOut(DBG3, laRaw & 0x01);
	debugOut(DBG4, laRaw & 0x02);
	debugOut(DBG5, laRaw & 0x40);
	debugOut(DBG6, laRaw & 0x80);
}

void resetSpeed() {
	MOTORS_LEFT = 100;
	MOTORS_RIGHT = 150;
}

void correctSteering() {
	unsigned char lineArrayRaw = readLineSensor();

	dbg(lineArrayRaw);

	setMotor(MOTOR_LEFT, MD_FWD);
	setMotor(MOTOR_RIGHT, MD_FWD);

	bool leftOuter = false;
	bool rightOuter = false;

	resetSpeed();

	if (lineArrayRaw & 0x01) {
		setMotor(MOTOR_RIGHT, MD_REV);
		MOTORS_RIGHT = 80;
		MOTORS_LEFT = 100;

		rightOuter = true;
		_delay_ms(30);
	} else if (lineArrayRaw & 0x02) {
		MOTORS_RIGHT = 50;
		_delay_ms(5);
	}

	// --------------
	if (lineArrayRaw & 0x80) {
		setMotor(MOTOR_LEFT, MD_REV);
		MOTORS_LEFT = 80;
		MOTORS_RIGHT = 100;

		leftOuter = true;
		_delay_ms(30);

	} else if (lineArrayRaw & 0x40) {
		MOTORS_LEFT = 50;
		_delay_ms(5);
	}

	//---------
	if (leftOuter && rightOuter) {
		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_REV);

		MOTORS_LEFT = 130;
		MOTORS_RIGHT = 60;

		_delay_ms(70);
	}
}
