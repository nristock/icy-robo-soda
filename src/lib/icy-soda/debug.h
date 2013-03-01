/*
 * debug.h
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <stdbool.h>

// left to right, LEDs at bottom
#define DBG1 PINC2
#define DBG2 PINC3
#define DBG3 PINC4
#define DBG4 PINC5
#define DBG5 PINC6
#define DBG6 PINC7

void enableDebug();
void debugOut(uint8_t output, bool enable);

#endif /* DEBUG_H_ */
