/*
 * main.c
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "lib/i2c/i2cmaster.h"
#include "lib/icy-soda/motor.h"
#include "lib/icy-soda/sensors.h"

int main() {
	DDRC = 0xff;

	i2c_init();
	unsigned char val = 0;

	while (1) {

		i2c_start_wait(0x02 + I2C_WRITE);
		i2c_write(0x44);
		i2c_rep_start(0x02 + I2C_READ);
		val = i2c_readNak();
		i2c_stop();

		PORTC = ~val;
	}
}
