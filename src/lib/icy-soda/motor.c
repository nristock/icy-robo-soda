/*
 * motor.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>

#include "motor.h"

void initMotors() {
	TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);
	TCCR1B = (1 << CS11) | (1 << CS10) | (1 << WGM12);

	TCCR2 = (1 << WGM21) | (1 << WGM20) | (1 << CS20) | (1 << COM21);

	OCR1A = 0;
	OCR2 = 0;

	DDRD |= (1 << PD5) | (1 << PD7);
	DDRD |= (1 << PD0) | (1 << PD1) | (1 << PD2) | (1 << PD3);
}

void setMotor(uint8_t motor, uint8_t motorDirection) {
	switch (motor) {
	case MOTOR_LEFT:
		if (motorDirection == MD_FWD) {
			PORTD |= (1 << PD0);
			PORTD &= ~(1 << PD1);
		} else if (motorDirection == MD_REV) {
			PORTD &= ~(1 << PD0);
			PORTD |= (1 << PD1);
		} else {
			PORTD &= ~(1 << PD0);
			PORTD &= ~(1 << PD1);
		}
		break;

	case MOTOR_RIGHT:
		if (motorDirection == MD_FWD) {
			PORTD |= (1 << PD3);
			PORTD &= ~(1 << PD2);
		} else if (motorDirection == MD_REV) {
			PORTD &= ~(1 << PD3);
			PORTD |= (1 << PD2);
		} else {
			PORTD &= ~(1 << PD3);
			PORTD &= ~(1 << PD2);
		}
		break;
	}
}
