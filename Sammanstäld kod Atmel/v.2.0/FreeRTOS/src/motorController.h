/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: filip
 */ 

#include <asf.h>
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_


void drive(uint8_t rSpeed, uint8_t lSpeed, int rDirection, int lDirection);
void testDriveR(uint8_t speed, int direction);
void testDriveL(uint8_t speed, int direction);
uint8_t getSetLSpeed(void);
uint8_t getSetRSpeed(void);
int getSetLDirection(void);
int getSetRDirection(void);
#endif /* MOTORCONTROLLER_H_ */