/*
 * main.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>
#include <util/delay.h>

#include <stdbool.h>

#include "lib/i2c/i2cmaster.h"
#include "lib/icy-soda/motor.h"
#include "lib/icy-soda/sensors.h"
#include "lib/icy-soda/debug.h"
#include "lib/icy-soda/anbuttons.h"

#include "steering.h"

#include "main.h"

#define ROTATE_TIME 1700

int main() {
	hardwareInit();

	while (1) {
#ifndef RELEASE
		handleAnalogButtonInterrupts();
#endif
		handleTouchInterrupts();

		correctSteering();
	}
}

void handleTouchInterrupts() {
	if (readButton(BTN_FRONT)) {
		debugOut(DBG1, true);

		MOTORS_LEFT = MOTORS_RIGHT = 100;

		setMotor(MOTOR_LEFT, MD_REV);
		setMotor(MOTOR_RIGHT, MD_REV);
		_delay_ms(1000);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_REV);
		_delay_ms(ROTATE_TIME);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_FWD);
		_delay_ms(1000);

		setMotor(MOTOR_LEFT, MD_REV);
		setMotor(MOTOR_RIGHT, MD_FWD);
		_delay_ms(ROTATE_TIME + 100);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_FWD);
		_delay_ms(2600);

		setMotor(MOTOR_LEFT, MD_REV);
		setMotor(MOTOR_RIGHT, MD_FWD);
		_delay_ms(ROTATE_TIME - 300);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_FWD);
		_delay_ms(1400);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_REV);
		_delay_ms(700);
	} else {
		debugOut(DBG1, false);
	}

	if (readButton(BTN_BACK)) {
		debugOut(DBG2, true);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_FWD);

		MOTORS_LEFT = 200;
		MOTORS_RIGHT = 255;

		while (!readButton(BTN_FRONT))
			_delay_ms(20);

		MOTORS_LEFT = MOTORS_RIGHT = 100;

		setMotor(MOTOR_LEFT, MD_REV);
		setMotor(MOTOR_RIGHT, MD_REV);
		_delay_ms(1000);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_REV);
		MOTORS_LEFT = MOTORS_RIGHT = 100;
		_delay_ms(ROTATE_TIME);

		setMotor(MOTOR_LEFT, MD_FWD);
		setMotor(MOTOR_RIGHT, MD_FWD);
		MOTORS_LEFT = 200;
		MOTORS_RIGHT = 255;
		_delay_ms(5000);

	} else {
		debugOut(DBG2, false);
	}
}

void handleAnalogButtonInterrupts() {
	if (isAnalogButtonDown(BTN_T4)) {
		bool invert = false;
		while (!isAnalogButtonDown(BTN_T1)) {
			_delay_ms(100);

			setMotor(MOTOR_LEFT, MD_STOP);
			setMotor(MOTOR_RIGHT, MD_STOP);

			debugOut(DBG1, invert);
			debugOut(DBG2, !invert);
			invert = !invert;
		}
		debugOut(DBG1, false);
		debugOut(DBG2, false);
	}
}

void hardwareInit() {
	DDRA = 0x00;

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

void doSomeCrazyStuffAtTheEnd() {
	while (1) {
		debugOut(DBG1, true);
		_delay_ms(150);
		debugOut(DBG1, false);
		debugOut(DBG2, true);
		_delay_ms(150);
		debugOut(DBG2, false);
		debugOut(DBG3, true);
		_delay_ms(150);
		debugOut(DBG3, false);
		debugOut(DBG4, true);
		_delay_ms(150);
		debugOut(DBG4, false);
		debugOut(DBG5, true);
		_delay_ms(150);
		debugOut(DBG5, false);
		debugOut(DBG6, true);
		_delay_ms(150);
		debugOut(DBG6, false);
	}
}
