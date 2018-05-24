
#ifndef NAVIGATION_H_
#define NAVIGATION_H_



#pragma once


void setDesiredSpeed(float dSpeedL, float dSpeedR);
int getDistanceToDestination(int x, int y);
void setExtension(int extension);
int getDistanceToDropOff(void);
int getDistanceToObject(void);
void driveCm(float cm,float velocity);
//void rotate(float degree,float angVel);
void rotate(int degree);
int getAngle(int p1X, int p1Y, int p2X, int p2Y);
float angleCorrection(int rX,int rY,int cX,int cY,int u1);
float getDesiredSpeedLeft(void);
float getDesiredSpeedRight(void);

#endif /* NAVIGATION_H_ */




