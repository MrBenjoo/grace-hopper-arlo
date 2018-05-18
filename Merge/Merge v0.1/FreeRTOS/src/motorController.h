/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: filip
 */ 

#include <asf.h>
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_


void testDriveL(float speedPulseL);
void testDriveR(float speedPulseR);
float getSetLeftSpeed(void);
float getSetRightSpeed(void);
int getSetLeftDirection(void);
int getSetRightDirection(void);
#endif /* MOTORCONTROLLER_H_ */