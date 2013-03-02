/*
 * anbuttons.h
 *
 *  Created on: Mar 2, 2013
 *      Author: nicolas
 */

#ifndef ANBUTTONS_H_
#define ANBUTTONS_H_

#include <stdbool.h>

#define BTN_T1 1
#define BTN_T2 2
#define BTN_T3 3
#define BTN_T4 4
#define BTN_T5 5

uint16_t getADC();
bool isAnalogButtonDown(uint8_t button);

#endif /* ANBUTTONS_H_ */
