/*
 * motor.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>

#include "motor.h"

void initMotors()
{
	TCCR1A = (1<<WGM10) | (1<<WGM11) | (1<<COM1A1) | (1<<COM1B1);
	TCCR1B = (1<<CS11) | (1<<CS10) |  (1<<WGM12) | (1<<WGM13);


	OCR1A =	0;
	OCR1B = 0;


	DDRD |= (1<<PD4) | (1<<	PD5);
	DDRD |= (1<<PD0) | (1<<PD1) | (1<<PD2) | (1<<PD3);
}

void setMotor(uint8_t motor, uint8_t motorDirection)
{
	switch(motor)
	{
		case MOTOR_LEFT:
			if(motorDirection == MD_REV)
			{
				PORTD |= (1 << PD0) | (0 << PD1);
			}
			else
			{
				PORTD |= (0 << PD0) | (1 << PD1);
			}
		break;

		case MOTOR_RIGHT:
			if(motorDirection == MD_REV)
			{
				PORTD |= (0 << PD2) | (1 << PD3);
			}
			else
			{
				PORTD |= (1 << PD2) | (0 << PD3);
			}
		break;
	}
}
