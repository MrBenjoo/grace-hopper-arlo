/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: filip
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_


void drive(int rSpeed, int lSpeed, int rDirection, int lDirection);
void testDriveR(int speed, int direction);
void testDriveL(int speed, int direction);
int getSetLSpeed(void);
int getSetRSpeed(void);
int getSetLDirection(void);
int getSetRDirection(void);
int rSpeedLatest;
int lSpeedLatest;
int rDirectionLatest;
int lDirectionLatest;
#endif /* MOTORCONTROLLER_H_ */