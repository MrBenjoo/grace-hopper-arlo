/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: filip
 */ 

#include <asf.h>
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_


void drive(double rSpeed, double lSpeed);
void testDriveR(double speed);
void testDriveL(double speed);
double getSetLSpeed(void);
double getSetRSpeed(void);
int8_t getSetLDirection(void);
int8_t getSetRDirection(void);
#endif /* MOTORCONTROLLER_H_ */