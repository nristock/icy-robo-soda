/*
 * debug.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#ifndef NO_DEBUG
#include <avr/io.h>
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
