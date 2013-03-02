/*
 * debug.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#ifndef NO_DEBUG
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#endif

#include "debug.h"

bool gDebugEnabled = false;

void enableDebug() {
#ifndef NO_DEBUG
	DDRC |= (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5) | (1 << PC6)
			| (1 << PC7);
	PORTC |= (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5) | (1 << PC6)
			| (1 << PC7);

	// check each LED
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
#endif
}

void debugOut(uint8_t output, bool enable) {
#ifndef NO_DEBUG
	enable = !enable; // invert since LEDs are enabled on low pin state
	if (enable) {
		PORTC |= (1 << output);
	} else {
		PORTC &= ~(1 << output);
	}
#endif
}
