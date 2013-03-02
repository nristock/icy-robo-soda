/*
 * anbuttons.c
 *
 *  Created on: Mar 2, 2013
 *      Author: nicolas
 */

#include <avr/io.h>

#include "anbuttons.h"

uint16_t getADC() {
	uint16_t value = 0;

	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	ADMUX = 7;

	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC)) {
	}
	value = ADCW;

	value = 0;
	for (uint8_t i = 0; i < 4; i++) {
		ADCSRA |= (1 << ADSC);
		while (ADCSRA & (1 << ADSC)) {
		}
		value = value + ADCW;
	}

	ADCSRA &= ~(1 << ADEN);

	value = value / 4;

	return value;
}


bool isAnalogButtonDown(uint8_t button) {
	uint16_t analog7 = getADC();

	if ((analog7 >= 337) && (analog7 <= 343) && button == BTN_T1) {
		return true;
	} else if ((analog7 >= 268) && (analog7 <= 274) && button == BTN_T2) {
		return true;
	} else if ((analog7 >= 200) && (analog7 <= 206) && BTN_T3) {
		return true;
	} else if ((analog7 >= 132) && (analog7 <= 138) && BTN_T4) {
		return true;
	} else if ((analog7 >= 64) && (analog7 <= 70) && BTN_T5) {
		return true;
	}

	return false;
}
