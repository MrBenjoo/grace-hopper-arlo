/*
 * motorController.h
 *
 *  Author: Group Grace Hopper
 */ 

#include <asf.h>
#include <stdio.h>
#include <math.h>
#include "../initializations/pins_init.h"

#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_


void testDriveL(float speedPulseL);
void testDriveR(float speedPulseR);
float getSetLeftSpeed(void);
float getSetRightSpeed(void);
int getSetLeftDirection(void);
int getSetRightDirection(void);

pwm_channel_t pwm_channel_instance;
 float mcPLeftLatest;
 float mcPRightLatest;
 int motorSpeed;
 

#endif /* MOTORCONTROLLER_H_ */






