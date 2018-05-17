/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: filip
 */ 

#include <asf.h>
#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_


void drive(uint8_t rSpeed, uint8_t lSpeed, int8_t rDirection, int8_t lDirection);
void testDriveR(uint8_t speed, int8_t direction);
void testDriveL(uint8_t speed, int8_t direction);
void rotate(int degree);
void driveCm(int cm);
int getAngle(int p1X, int p1Y, int p2X, int p2Y);
int angleCorrection(int rX,int rY,int cX,int cY,int u1);
uint8_t getSetLSpeed(void);
uint8_t getSetRSpeed(void);
int8_t getSetLDirection(void);
int8_t getSetRDirection(void);
#endif /* MOTORCONTROLLER_H_ */