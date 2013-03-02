/*
 * motor.h
 *
 *  Created on: Mar 1, 2013
 *      Author: nicolas
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#define MOTOR_LEFT 1
#define MOTOR_RIGHT 2

#define MOTORS_LEFT OCR1A
#define MOTORS_RIGHT OCR2

#define MD_STOP 0
#define MD_FWD 1
#define MD_REV 2

void initMotors();
void setMotor(uint8_t motor, uint8_t direction);

#endif /* MOTOR_H_ */
