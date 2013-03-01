/*
 * sensors.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>

#include "sensors.h"

void initSensors() {
	DDRB |= (0<<PB0) | (0<<PB1);

	PORTB |= (1<<PB0) | (0<<PB1);

}

int readButton(uint8_t button)
{
	switch(button) {
		case BTN_BACK:
			return PINB & (1<<PB0);
		break;
		case BTN_FRONT:
			return PINB & (1<<PB1);
		break;
	}
}
