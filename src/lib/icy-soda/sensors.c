/*
 * sensors.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#include <avr/io.h>
#include <stdbool.h>

#include "../i2c/i2cmaster.h"
#include "sensors.h"

void initSensors() {
	DDRB |= (0 << PB0) | (0 << PB1);
	PORTB |= (1 << PB0) | (1 << PB1);

	i2c_init();
}

bool readButton(uint8_t button) {
	switch (button) {
	case BTN_BACK:
		return (PINB & (1 << PB0)) ? false : true;
		break;
	case BTN_FRONT:
		return (PINB & (1 << PB1)) ? false : true;
		break;
	default:
		return false;
	}
}

unsigned char readLineSensor() {
	unsigned char value = 0;

	i2c_start_wait(0x02 + I2C_WRITE);
	i2c_write(0x44); // "result" register -> set bits mark sensors which "see" black
	i2c_rep_start(0x02 + I2C_READ);
	value = i2c_readNak();
	i2c_stop();

	return value;
}
