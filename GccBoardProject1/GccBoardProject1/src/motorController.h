/*
 * motorController.h
 *
 * Created: 2018-04-18 13:02:08
 *  Author: Filip och Carl
 */ 


#ifndef MOTORCONTROLLER_H_
#define MOTORCONTROLLER_H_

void drive(int rSpeed, int lSpeed, int rDirection, int lDirection);
void testDriveR(int speed, int direction);
void testDriveL(int speed, int direction);
void angleCorrection(int rX,int rY,int cX,int cY,int u1);
int getAngle(int p1X, int p1Y, int p2X, int p2Y);

#endif /* MOTORCONTROLLER_H_ */