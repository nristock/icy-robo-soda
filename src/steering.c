/*
 * steering.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>

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

	unsigned char lWeight = 0;
	if (lineArrayRaw & 0b10000000) {
		lWeight += 30;
	}
	if (lineArrayRaw & 0b01000000) {
		lWeight += 20;
	}
	if (lineArrayRaw & 0b00100000) {
		lWeight += 10;
	}
	MOTORS_LEFT = 0;


	//
	unsigned char rWeight = 0;
	if (lineArrayRaw & 0x01) {
		rWeight += 30;
	}
	if (lineArrayRaw & 0x02) {
		rWeight += 20;
	}
	if (lineArrayRaw & 0x04) {
		rWeight += 10;
	}
	MOTORS_RIGHT = 255 - (rWeight * 4);
}
