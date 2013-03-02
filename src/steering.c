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

//TODO: speed needs proper scaling and motor specific offset fixes

void dbg(unsigned char laRaw) {
	debugOut(DBG3, laRaw & 0x01);
	debugOut(DBG4, laRaw & 0x04);
	debugOut(DBG5, laRaw & 0x08);
	debugOut(DBG6, laRaw & 0x20);
}

void correctSteering() {
	unsigned char lineArrayRaw = readLineSensor();

	dbg(lineArrayRaw);

	setMotor(MOTOR_LEFT, MD_FWD);
	setMotor(MOTOR_RIGHT, MD_FWD);

	bool leftRev = false;
	bool rightRev = false;

	bool leftOuter = false;
	bool rightOuter = false;

	unsigned char rWeight = 0;
	if (lineArrayRaw & 0x01) {
		rWeight += 100;
		rightOuter = true;
		if (!leftRev) {
			setMotor(MOTOR_RIGHT, MD_REV);
			rightRev = true;
			_delay_ms(75);
		}
	}
	if (lineArrayRaw & 0x02) {
		rWeight += 80;
		if (!leftRev) {
			setMotor(MOTOR_RIGHT, MD_REV);
			rightRev = true;
			_delay_ms(75);
		}
	}
	if (lineArrayRaw & 0x04) {
		rWeight += 60;
	}
	if ((MAX_MOTOR_SPEED - (rWeight * 2)) < 70) {
		MOTORS_RIGHT = 70 + 30;
	} else {

		MOTORS_RIGHT = MAX_MOTOR_SPEED + 50 - (rWeight * 2);
	}

	unsigned char lWeight = 0;
	if (lineArrayRaw & 0b10000000) {
		lWeight += 100;
		leftOuter = true;
		if (!rightRev) {
			setMotor(MOTOR_LEFT, MD_REV);
			leftRev = true;
			_delay_ms(75);
		}

	}
	if (lineArrayRaw & 0b01000000) {
		lWeight += 80;
		if (!rightRev) {
			setMotor(MOTOR_LEFT, MD_REV);
			leftRev = true;
			_delay_ms(75);
		}
	}
	if (lineArrayRaw & 0b00100000) {
		lWeight += 60;
	}
	if ((MAX_MOTOR_SPEED - (lWeight * 2)) < 70) {
		MOTORS_LEFT = 70;
	} else {
		MOTORS_LEFT = MAX_MOTOR_SPEED - (lWeight * 2);
	}

	if (leftOuter && rightOuter) {
		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_REV);

		MOTORS_LEFT = 110;
		MOTORS_RIGHT = 60;

		_delay_ms(70);
	}
}
